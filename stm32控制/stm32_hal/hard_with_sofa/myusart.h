#ifndef __myusart_H__
#define __myusart_H__

#include "sys.h"


#define FRAME_SIZE 18
#define BUFFER_SIZE  100  

extern uint16_t current_count1;
extern uint16_t current_count3;
extern  volatile uint8_t rx1_len ;  //接收一帧数据的长度
extern  volatile uint8_t rx3_len ;  //接收一帧数据的长度
extern uint8_t rx1_buffer[100];  //接收数据缓存数组
extern uint8_t rx3_buffer[100];  //接收数据缓存数组
extern volatile uint16_t type , x , y , n ;
extern volatile uint8_t K_key;

void usart_rx(int rx);
void process_received_data3(uint16_t length);
void process_received_data1(uint16_t length);
void UART_SendString(const char* str);
int fputc(int ch, FILE *f);
void UART3_SendString(const char* str);

#endif
