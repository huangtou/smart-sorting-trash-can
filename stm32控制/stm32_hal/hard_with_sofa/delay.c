#include "sys.h"
/*
for循环实现延时us
*/
void for_delay_us(uint32_t nus)
{
 uint32_t Delay = nus * 168/4;
 do
 {
  __NOP();
 }
 while (Delay --);
}

void for_delay_ms(uint32_t nms)
{
 nms*=100;
 do
 {
  for_delay_us(10);
 }
 while (nms --);
}

