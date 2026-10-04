#ifndef __PCA9685_H
#define __PCA9685_H
#include "sys.h"
//IO方向设置

#define SDA_IN()  {GPIOC->MODER&=~(3<<(7*2));GPIOC->MODER|=0<<7*2;}	//PC7输入模式
#define SDA_OUT() {GPIOC->MODER&=~(3<<(7*2));GPIOC->MODER|=1<<7*2;} //PC7输出模式

#define PCA_Addr 0x80
#define PCA_Model 0x00
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define PCA_Pre 0xFE

//IO操作函数	 
#define IIC_SCL    PCout(8) //SCL
#define IIC_SDA    PCout(7) //SDA	 
#define READ_SDA   PCin(7)  //输入SDA

//IIC所有操作函数		 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
 
void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  


void PCA9685_Init(float hz,uint16_t angle);
void PCA9685_Write(uint8_t addr,uint8_t data);
uint8_t PCA9685_Read(uint8_t addr);
void PCA9685_setPWM(uint8_t num,uint32_t on,uint32_t off);
void PCA9685_setFreq(float freq);
void setAngle90(uint8_t num,uint16_t angle);
void setAngle180(uint8_t num,uint16_t angle);
void setAngle270(uint8_t num,uint16_t angle);
void setAngle360(uint8_t num,uint16_t angle);
void recycle(int num);

#endif
