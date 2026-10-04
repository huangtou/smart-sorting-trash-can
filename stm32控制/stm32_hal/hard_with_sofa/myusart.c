#include "sys.h"

extern uint8_t cam_flag;
extern uint8_t hmi_flag;
uint8_t rx1_buffer[100]={0};  
uint8_t rx3_buffer[100]={0};  					//DMA接收缓冲区
volatile uint8_t rx1_len= 0;            	    //当前写入索引
volatile uint8_t rx3_len= 0;            	    //当前写入索引

volatile uint16_t type = 0, x = 0, y = 0, n = 0;
volatile uint8_t K_key=0;
uint16_t current_count1=0;
uint16_t current_count3=0;

void usart_rx(int rx)
{
	switch(rx)
	{
		case 1:
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
			HAL_UART_Receive_DMA(&huart1,rx1_buffer,BUFFER_SIZE);
			break;
		case 3:
			__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);
			HAL_UART_Receive_DMA(&huart3,rx3_buffer,BUFFER_SIZE); 
			break;
		case 11:
			__HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);
			break;
		case 33:
			__HAL_UART_DISABLE_IT(&huart3, UART_IT_IDLE);
			break;
		default:break;
	}
}

/* USART3数据协议解析 */
void process_received_data3(uint16_t length)
{
    static uint8_t frame_buffer[FRAME_SIZE];
    static uint8_t frame_index = 0;
    static uint8_t state = 0;
    
    for(uint16_t i=0; i<length; i++)
    {
        uint8_t data = rx3_buffer[i];
        
        switch(state)
        {
            case 0: // 等待帧头0x2C
                if(data == 0x2C)
                {
                    frame_index = 0;
                    frame_buffer[frame_index++] = data;
                    state = 1;
                }
                break;
            case 1: // 验证长度字段
                if(data == 0x2E)  // 协议长度字段
                {
                    frame_buffer[frame_index++] = data;
                    state = 2;
                }
                else
                {
                    state = 0;
                }
                break;
            case 2: // 接收数据
                frame_buffer[frame_index++] = data;
                if(frame_index > FRAME_SIZE-1||data == 0x5B) // 预留校验位
                {
                    state = 3;
                }
                break;
            case 3: // 校验帧尾
                if(frame_buffer[frame_index-1] == 0x5B)
                {
                  
                    type   = (frame_buffer[3] << 8) | frame_buffer[2];
                    x      = (frame_buffer[5] << 8) | frame_buffer[4];
                    y      = (frame_buffer[7] << 8) | frame_buffer[6];
                    n      = (frame_buffer[9] << 8) | frame_buffer[8];
					cam_flag=1;
                    
                }
                state = 0;
                break;
        }
    }
	memset(rx3_buffer,0,rx3_len);
}


//HAL_UART_Transmit()//


int fputc(int ch, FILE *f)
{  
	 
	/* 堵塞判断串口是否发送完成 */
  while((USART1->SR & 0X40) == RESET);
	
	/* 串口发送完成，将该字符发送 */
	USART1->DR = (uint8_t)ch;  
	
  return ch;
}

void UART_SendString(const char* str)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 0xffff);
}

void UART3_SendString(const char* str)
{
    HAL_UART_Transmit(&huart3, (uint8_t*)str, strlen(str), 0xffff);
}


