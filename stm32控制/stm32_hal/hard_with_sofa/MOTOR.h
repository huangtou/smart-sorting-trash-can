#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

int GD(int i);
void MOTOR_Init(void);
void compress(int comp);
void move(float m_x,float m_y);
void speed(int16_t s_x,int16_t s_y);
void assign(int n0,int n1,int n2,int n3,int x1,int x2,int z,int k);

#endif

