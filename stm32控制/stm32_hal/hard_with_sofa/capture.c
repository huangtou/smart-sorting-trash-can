#include "capture.h"

extern uint16_t angle_0;
extern uint16_t angle_1;
extern uint16_t angle_2;
extern uint16_t angle_3;
extern uint16_t angle_4;
extern uint16_t angle_5;
extern uint16_t angle_6;
extern uint16_t angle_7;
extern uint16_t angle_8;

extern uint16_t n_0;//YH
extern uint16_t n_1;//KHS
extern uint16_t n_2;//CY
extern uint16_t n_3;//QT
extern uint16_t x1;



float err_x=4.0/220;
float err_y=3.8/265;

void control(int i1,int i2)
{
	float mo_x=0;
	float mo_y=0;
	int k;
	switch(i1)
	{
		case 0:{setAngle270(0,angle_0); setAngle270(1,angle_1); setAngle270(2,angle_2); setAngle270(3,angle_3);setAngle270(4,angle_4);for_delay_ms(500);
				setAngle270(5,angle_5+35); setAngle270(6,angle_6+38); setAngle270(7,angle_7+35); setAngle270(8,angle_8+35);}break; //reset_SHU
		case 1:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0+45); setAngle270(1,angle_1);setAngle270(2,angle_2);setAngle270(3,angle_3); }break; //WAI
		case 2:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0); setAngle270(1,angle_1); setAngle270(2,angle_2);setAngle270(3,angle_3); }break;//HE 
		case 11:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0+45); setAngle270(1,angle_1+45); }break; 
		case 22:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0-45); setAngle270(1,angle_1+45); }break; 
		case 33:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0+45); setAngle270(1,angle_1-45); }break; 
		case 44:{setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(500);
				setAngle270(0,angle_0-45); setAngle270(1,angle_1-45); }break; 
	
	}
	switch(i2)
	{

		case 100:{}break;
		case 0:{
				Emm_V5_Pos_Control(1, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0); 
				while(GD(1)){}
				Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
				Emm_V5_Pos_Control(1, 1, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
				while(GD(2)){}
				Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
			   }break; 

		case 1:{
				for_delay_ms(1500);
				while(1)
				{
					UART3_SendString("FSSJ");
					for_delay_ms(1000);
					if (n)
					{
						for_delay_ms(1500);
						UART3_SendString("FSSJ");
						break;
					}
				}
				printf("n5.val=%d\xFF\xFF\xFF",type);
				switch (type)
				{
					case 0:{k=1;}break;
					case 1:{k=1;}break;//YH
					case 11:{k=1;}break;//YH
					case 12:{k=1;}break;//YH
		
					case 2:{k=2;}break;
					case 3:{k=2;}break;
					case 9:{k=2;}break;//KHS
					
					case 4:{k=3;}break;
					case 5:{k=3;}break;
					case 6:{k=3;}break;//CY
					case 10:{k=3;}break;//CY
					case 13:{k=3;}break;//CY
					
					case 7:{k=4;}break;
					case 8:{k=4;}break;//QT
				}
				assign(n_0,n_1,n_2,n_3,x1,1,0,k);
				setAngle270(5,angle_5); setAngle270(6,angle_6); setAngle270(7,angle_7); setAngle270(8,angle_8);for_delay_ms(1000);setAngle270(0,angle_0);//kai
				
				if (n==2)//zhuan90-zhua
				{
					mo_x=((390-y)*err_x+0.4);
					mo_y=(((220-x)*err_y-0.3));
				
					move(mo_x,mo_y);
					setAngle270(4,angle_4-90);//zhuan
					for_delay_ms(1000);
					setAngle270(3,angle_3-90);//xia
					for_delay_ms(1000);
					setAngle270(2,angle_2+50);//zhua
					for_delay_ms(1000);
					setAngle270(3,angle_3);//shang
					for_delay_ms(1000);
					setAngle270(4,angle_4);//zhuan
				}
				if (n==3)//zhijie-zhua
				{
					mo_x=((390-y)*err_x+0.2);
					mo_y=(((220-x)*err_y));
					
					move(mo_x,mo_y);//y-xia
					for_delay_ms(1000);
					setAngle270(3,angle_3-90);//xia
					for_delay_ms(1000);
					setAngle270(2,angle_2+50);//zhuan
					for_delay_ms(1000);
					setAngle270(3,angle_3);
				}
					for_delay_ms(1000);
					setAngle270(0,angle_0+45);
				
				if (type==0 || type==1  || type==11 || type==12)//YH
				{
					n_0++;
				}
				else if (type==4 || type==5 || type==10 || type==13)//CY
				{
					n_2++;
					
				}
				else if (type==2 || type==3 || type==9)//KHS
				{
					n_1++;
					
				}
				else if (type==7 || type==8)//QT
				{
					n_3++;
					
				}
				
				if (type==0 || type==1 || type==11 || type==12)//YH
				{

					mo_x=5.0-mo_x;
					
					Emm_V5_Pos_Control(1, 1, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					while(GD(2)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					move(mo_x,0);
					setAngle270(2,angle_2);
					for_delay_ms(1000);
					control(2,0);
				}
				
				else if (type==4 || type==5 || type==6 || type==10 || type==13)//CY
				{
					
					Emm_V5_Pos_Control(1, 1, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					while(GD(2)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
						
					Emm_V5_Pos_Control(1, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0); 
					while(GD(1)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					setAngle270(2,angle_2);
					for_delay_ms(1000);
					
				}
				else if (type==2 || type==3 || type==9)//KHS
				{

					mo_y=(-4.3-mo_y);
					mo_x=(5.0-(390-y)*err_x);
					
					setAngle270(4,angle_4-90);//zhuan
					for_delay_ms(500);
					move(0,mo_y);
					move(mo_x,0);
					setAngle270(2,angle_2);
					for_delay_ms(1000);
					Emm_V5_Pos_Control(1, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0); 
					while(GD(1)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
						
					setAngle270(4,angle_4);//zhuan	
					for_delay_ms(1000);
					
					Emm_V5_Pos_Control(1, 1, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					while(GD(2)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					
				}
				else if (type==7 || type==8)//QT
				{
					
					mo_y=(-4.3-mo_y);
					
					setAngle270(4,angle_4-90);//zhuan
					for_delay_ms(500);
					move(0,mo_y);
					Emm_V5_Pos_Control(1, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0); 
					while(GD(1)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);

					setAngle270(2,angle_2);
					setAngle270(4,angle_4);//zhuan
					for_delay_ms(1000);
					setAngle270(4,angle_4);//zhuan
					for_delay_ms(1000);
					Emm_V5_Pos_Control(1, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Pos_Control(2, 0, 100, 0, 20000, 0, 1);HAL_Delay(10);Emm_V5_Synchronous_motion(0); 
					while(GD(1)){}
					Emm_V5_Stop_Now(1,1);HAL_Delay(10);Emm_V5_Stop_Now(2,1);HAL_Delay(10);Emm_V5_Synchronous_motion(0);HAL_Delay(10);
					control(2,0);
						
				}
				
			   assign(n_0,n_1,n_2,n_3,x1,1,1,k);
			   type = 0;
			   x = 0;
			   y = 0;
			   n = 0;
			   x1++;
			   }
			   break; 	   
	}
}

void initial(void)
{

	int k;
	htim4.Instance->CCR2 = 30;
	for_delay_ms(1500);
	while(1)
	{
		if (GD3==0) {printf("s1.txt=\"ÊÇ\"\xFF\xFF\xFF");}
		else {printf("s1.txt=\"·ñ\"\xFF\xFF\xFF");}
		UART3_SendString("FS");
		for_delay_ms(500);
		if (n)
		{
			for_delay_ms(1000);
			break;
		}
	}
	UART3_SendString("FS");
	switch (type)
	{
		case 0:{k=1;}break;
		case 1:{k=1;}break;//YH
		
		case 2:{k=2;}break;
		case 3:{k=2;}break;
		case 9:{k=2;}break;//KHS
		
		case 4:{k=3;}break;
		case 5:{k=3;}break;//CY
		case 6:{k=3;}break;
		
		case 7:{k=4;}break;
		case 8:{k=4;}break;//QT

	}
	
	assign(n_0,n_1,n_2,n_3,x1,1,0,k);
	
	if (type==0 || type==1)//YH
	{
		control(22,100);
		for_delay_ms(1000);
		n_0++;
	}
	else if (type==4 || type==5 || type==6)//CY
	{
		control(11,100);
		for_delay_ms(1000);
		n_2++;
		
	}
	else if (type==2 || type==3 || type==9)//KHS
	{
		control(33,100);
		for_delay_ms(1000);
		n_1++;
		
	}
	else if (type==7 || type==8)//QT
	{
		control(44,100);
		for_delay_ms(1000);
		n_3++;
		
	}
	assign(n_0,n_1,n_2,n_3,x1,1,1,k);
	control(0,100);
	for_delay_ms(1000);
	x1++;
	type = 0;
	x = 0;
	y = 0;
	n = 0;
	if (GD3==0) {printf("s1.txt=\"ÊÇ\"\xFF\xFF\xFF");}
	else {printf("s1.txt=\"·ñ\"\xFF\xFF\xFF");}

}

