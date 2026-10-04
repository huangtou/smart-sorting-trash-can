#include "sys.h"

extern uint16_t angle_0;
extern uint16_t angle_1;
extern uint16_t angle_2;
extern uint16_t angle_3;
extern uint16_t angle_4;
extern uint16_t angle_5;
extern uint16_t angle_6;
extern uint16_t angle_7;
extern uint16_t angle_8;

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	for_delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	for_delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	for_delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	for_delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;for_delay_us(1);	   
	IIC_SCL=1;for_delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	for_delay_us(2);
	IIC_SCL=1;
	for_delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	for_delay_us(2);
	IIC_SCL=1;
	for_delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		for_delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		for_delay_us(2); 
		IIC_SCL=0;	
		for_delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        for_delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		for_delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


void PCA9685_Init(float hz,uint16_t angle)
{
//	uint32_t off = 0;
	PCA9685_Write(PCA_Model,0x00);
	PCA9685_setFreq(hz);
	setAngle270(0,angle_0);
	setAngle270(1,angle_1);
	setAngle270(2,angle_2);
	setAngle270(3,angle_3);
	setAngle270(4,angle_4);
	setAngle270(5,angle_5);
	setAngle270(6,angle_6);
	setAngle270(7,angle_7);
	setAngle270(8,angle_8);
	
	
//  off = (uint32_t)(103+angle*2.28);  //360度舵机，每转动一度=1.14   0度起始位置：103
//	PCA9685_setPWM(0,0,off);
//	PCA9685_setPWM(1,0,off);
//	PCA9685_setPWM(2,0,off);
//	PCA9685_setPWM(3,0,off);
//	PCA9685_setPWM(4,0,off);
//	PCA9685_setPWM(5,0,off);
//	PCA9685_setPWM(6,0,off);
//	PCA9685_setPWM(7,0,off);
//	PCA9685_setPWM(8,0,off);
//	PCA9685_setPWM(9,0,off);
//	PCA9685_setPWM(10,0,off);
//	PCA9685_setPWM(11,0,off);
//	PCA9685_setPWM(12,0,off);
//	PCA9685_setPWM(13,0,off);
//	PCA9685_setPWM(14,0,off);
//	PCA9685_setPWM(15,0,off);
	for_delay_ms(100);
	
}
 
void PCA9685_Write(uint8_t addr,uint8_t data)    //   addr 表示要写入数据的寄存器地址，data 表示要写入的数据
{
	IIC_Start();                         //   发送 I2C 起始信号，开始 I2C 通信。
	
	IIC_Send_Byte(PCA_Addr);             //   发送 PCA9685 的地址，告诉设备我们要和 PCA9685 进行通信。
	IIC_NAck();                          //   发送不应答信号，表示主控器不需要从设备接收更多数据。
	
	IIC_Send_Byte(addr);                 //   发送要写入数据的寄存器地址。
	IIC_NAck();                          //   发送不应答信号。
	
	IIC_Send_Byte(data);                 //   发送要写入的数据。
	IIC_NAck();                          //   发送不应答信号。
	
	IIC_Stop();                          //   发送 I2C 停止信号，结束本次通信。
	
}
 
uint8_t PCA9685_Read(uint8_t addr)                //   addr 表示要读取数据的寄存器地址
{
	uint8_t data;                              //   声明一个无符号 8 位整数变量 data，用于存储读取到的数据。
	
	IIC_Start();                          //   发送 I2C 起始信号，开始 I2C 通信。
	
	IIC_Send_Byte(PCA_Addr);              //   发送 PCA9685 的地址，告诉设备我们要和 PCA9685 进行通信。
	IIC_NAck();                           //   发送不应答信号，表示主控器不需要从设备接收更多数据。
	 
	IIC_Send_Byte(addr);                  //   发送要读取数据的寄存器地址。
	IIC_NAck();                           //   发送不应答信号。
	
	IIC_Stop();                           //   发送 I2C 停止信号，结束本次通信。
	
	for_delay_us(10);                         //   延时 10 微秒，等待芯片准备好数据。
 
	
	IIC_Start();                          //   发送 I2C 起始信号，开始另一次 I2C 通信。
 
	IIC_Send_Byte(PCA_Addr|0x01);         //   发送 PCA9685 的地址，并设置最低位为 1，表示要进行读取操作。
	IIC_NAck();                           //   发送不应答信号。
	 
	data = IIC_Read_Byte(0);              //   通过 I2C 从 PCA9685 读取一个字节的数据，并存储到变量 data 中。
	
	IIC_Stop();                           //   发送 I2C 停止信号，结束本次通信。
	
	return data;                          //   返回读取到的数据。
	
}
 
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off)   //num 表示 PWM 通道号，on 表示 PWM 的起始位置，off 表示 PWM 的结束位置（即从高电平切换到低电平的时刻）
{
	IIC_Start();                              //发送 I2C 起始信号，开始 I2C 通信。
	
	IIC_Send_Byte(PCA_Addr);                  //发送 PCA9685 的地址，告诉设备我们要和 PCA9685 进行通信。
	IIC_Wait_Ack();                           //等待应答信号，确保设备准备好接收数据。
 
	IIC_Send_Byte(LED0_ON_L+4*num);           //发送 LED 寄存器的地址，根据 PWM 通道号计算出相应的寄存器地址。
	IIC_Wait_Ack();                           //
	
	IIC_Send_Byte(on&0xFF);                   //发送 PWM 的起始位置低 8 位。
	IIC_Wait_Ack();                           //等待应答信号。
	 
	IIC_Send_Byte(on>>8);                     //发送 PWM 的起始位置高 8 位。
	IIC_Wait_Ack();                           //等待应答信号。
	
	IIC_Send_Byte(off&0xFF);                  //发送 PWM 的结束位置低 8 位。
	IIC_Wait_Ack();                           //等待应答信号。
	
	IIC_Send_Byte(off>>8);                    //发送 PWM 的结束位置高 8 位。
	IIC_Wait_Ack();                           //等待应答信号。
	
	IIC_Stop();                              //发送 I2C 停止信号，结束本次通信。
	
}
 
void PCA9685_setFreq(float freq)
{
	uint8_t prescale,oldmode,newmode;              //定义了三个无符号 8 位整型变量 用于存储预分频器值、旧的模式寄存器值和新的模式寄存器值
	double prescaleval;                       //定义了一个双精度浮点型变量 prescaleval，用于计算预分频器的值。
	freq*= 0.98f;                              //将传入的频率值乘以 0.98，这是为了微调频率值以适应 PCA9685 的实际需求
	prescaleval = 25000000;                   //这是 PCA9685 内部振荡器的频率
	prescaleval /= 4096;                      //每个周期从0计数到4095，除以 4096，得到每个计数器周期的时间，
	prescaleval /= freq;                      //除以所需的频率值，得到预分频器的值。
	prescaleval -= 1;                         //减去 1，得到最终的预分频器值
	prescale = floor(prescaleval+0.5f);       //将计算得到的预分频器值四舍五入取整，并将其赋值给 prescale 变量。
	oldmode = PCA9685_Read(PCA_Model);        //通过调用 PCA9685_Read 函数读取当前 PCA9685 寄存器中的模式值，并将其存储在 oldmode 变量中。
	
	newmode = (oldmode&0x7F)|0x10;            //根据旧的模式值计算出新的模式值，将最高位清零（bit 7）并将第 5 位设为1（bit 4），表示将 PCA9685 设置为睡眠模式。
	PCA9685_Write(PCA_Model,newmode);         //将新的模式值写入 PCA9685 的模式寄存器。
	PCA9685_Write(PCA_Pre,prescale);          //将计算得到的预分频器值写入 PCA9685 的预分频器寄存器。
	PCA9685_Write(PCA_Model,oldmode);         //恢复旧的模式值。
	for_delay_ms(5);                              // 延时 5 毫秒，等待 PCA9685 完全启动。
	PCA9685_Write(PCA_Model,oldmode|0xa1);    //将模式值的最高位和第 1 位设为1，表示将 PCA9685 设置为正常工作模式。
	
}
void setAngle180(uint8_t num,uint16_t angle)
{
	uint32_t off = 0;                
	off = (uint32_t)(103+angle*2.28);  //360度舵机，每转动一度=1.14   0度起始位置：103
	PCA9685_setPWM(num,0,off);
}
void setAngle360(uint8_t num,uint16_t angle)
{
	uint32_t off = 0;                
	off = (uint32_t)(103+angle*1.14);  //360度舵机，每转动一度=1.14   0度起始位置：103
	PCA9685_setPWM(num,0,off);
}
void setAngle270(uint8_t num,uint16_t angle)
{
	uint32_t off = 0;                
	off = (uint32_t)(103+angle*1.52);  //360度舵机，每转动一度=1.14   0度起始位置：103
	PCA9685_setPWM(num,0,off);
}
void setAngle90(uint8_t num,uint16_t angle)
{
	uint32_t off = 0;                
	off = (uint32_t)(103+angle*4.56);  //360度舵机，每转动一度=1.14   0度起始位置：103
	PCA9685_setPWM(num,0,off);
}
void recycle(int num)
{
	switch(num)
	{
		case 0:{setAngle270(3,angle_1+35); setAngle180(4,angle_2+35); setAngle270(5,angle_3+35); setAngle180(6,angle_4+35);for_delay_ms(300); setAngle270(1,157-80);for_delay_ms(300);setAngle270(2,140-65);}break; //1、正为逆时针
		case 1:{setAngle270(3,angle_1+35); setAngle180(4,angle_2+35); setAngle270(5,angle_3+35); setAngle180(6,angle_4+35);for_delay_ms(300); setAngle270(1,157-80);for_delay_ms(300);setAngle270(2,140-65);}break; //1、正为逆时针
		case 2:{setAngle270(3,angle_1+35); setAngle180(4,angle_2+35); setAngle270(5,angle_3+35); setAngle180(6,angle_4+35);for_delay_ms(300); setAngle270(1,157);for_delay_ms(300);setAngle270(2,140-65);}break; 
		case 3:{setAngle270(3,angle_1+35); setAngle180(4,angle_2+35); setAngle270(5,angle_3+35); setAngle180(6,angle_4+35);for_delay_ms(300); setAngle270(1,157-95);for_delay_ms(300);setAngle270(2,140+65);}break; //1、正为逆时针
		case 4:{setAngle270(3,angle_1+35); setAngle180(4,angle_2+35); setAngle270(5,angle_3+35); setAngle180(6,angle_4+35);for_delay_ms(300); setAngle270(1,157);for_delay_ms(300);setAngle270(2,140+65);}break;
		case 5:{setAngle270(1,157);setAngle270(2,140);for_delay_ms(500);setAngle270(3,angle_1); setAngle180(4,angle_2); setAngle270(5,angle_3); setAngle180(6,angle_4);}break; 			
	}
}
