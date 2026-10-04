#include "MOTOR.h"
int counts=0;
//获取光电值
int GD(int i)
{
	int a;
	switch(i)
	{
		case 1:a=GD1;break;
		case 2:a=GD2;break;		
		case 3:a=GD3;break;
		
		default:a=-1;break;
	}
	return a;
}

void MOTOR_Init(void)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	htim4.Instance->CCR1 = 900;
//	htim4.Instance->CCR2 = 50;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	USER_CAN1_Filter_Init();
	if(HAL_CAN_Start(&hcan1) != HAL_OK) { Error_Handler(); }	
	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) { Error_Handler(); }
	HAL_Delay(1000);
}

void compress(int comp)
{
	switch(comp)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
			break;	
	}
}

void move(float m_x,float m_y)
{
	int direr=0;
	int direr_1=0;
	int direr_2=0;
	
	if      (m_x<0) { direr=0; m_x=-m_x;}
	else if (m_x>0) { direr=1;}
	if      (m_y<0) { direr_1=0; direr_2=1;  m_y=-1.0*m_y;}
	else if (m_y>0) { direr_1=1; direr_2=0;}
	if(m_x!=0)
	{
		Emm_V5_Pos_Control(1, direr, 100, 0,(int)3200*m_x, 0, 1);
		HAL_Delay(10);
		Emm_V5_Pos_Control(2, direr, 100, 0, (int)3200*m_x, 0, 1);
		HAL_Delay(10);
		Emm_V5_Synchronous_motion(0);
		while(1){for_delay_ms(10);counts++;if(counts==(int)( (m_x)*90 )){ counts=0; break;}}; can.rxFrameFlag = false;
	}
	HAL_Delay(10);
	if (m_y!=0)
	{
		Emm_V5_Pos_Control(1, direr_1, 100, 0, (int)(3200*m_y), 0, 1);
		HAL_Delay(10);
		Emm_V5_Pos_Control(2, direr_2, 100, 0, (int)(3200*m_y), 0, 1);
		HAL_Delay(10);
		Emm_V5_Synchronous_motion(0);
		while(1){for_delay_ms(10);counts++;if(counts==(int)( (m_y)*90 )){ counts=0; break;}}; can.rxFrameFlag = false;
		
	}	
}

void assign(int n0,int n1,int n2,int n3,int x1,int x2,int z,int k)//
{
	printf("n0.val=%d\xFF\xFF\xFF",n0);
	printf("n0.val=%d\xFF\xFF\xFF",n0);
	printf("n1.val=%d\xFF\xFF\xFF",n1);
	printf("n2.val=%d\xFF\xFF\xFF",n2);
	printf("n3.val=%d\xFF\xFF\xFF",n3);
	printf("x1.val=%d\xFF\xFF\xFF",x1);
	printf("x2.val=%d\xFF\xFF\xFF",x2);

	switch (z)
	{
		case 0:{printf("t3.txt=\"未完成\"\xFF\xFF\xFF");}break;
		case 1:{printf("t3.txt=\"完成\"\xFF\xFF\xFF");}break;
	}
	switch (k)
	{
		case 1:{printf("t1.txt=\"有害垃圾\"\xFF\xFF\xFF");}break;
		case 2:{printf("t1.txt=\"可回收垃圾\"\xFF\xFF\xFF");}break;
		case 3:{printf("t1.txt=\"厨余垃圾\"\xFF\xFF\xFF");}break;
		case 4:{printf("t1.txt=\"其他垃圾\"\xFF\xFF\xFF");}break;
	}
	

}
