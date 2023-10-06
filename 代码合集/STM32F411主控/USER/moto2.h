#ifndef __MOTO2_H
#define __MOTO2_H
#include "sys.h"

void MOTO2_TIM3_A4950_Init(int KHZ);

void MOTO2_TIM3_TB6122_Init(int KHZ);
void MOTO_IO_Init(void); //PB 0 1 2 10


void moto_duty1(float duty);
void moto_duty2(float duty);
void moto_duty3(float duty);
void moto_duty4(float duty);

void moto_mov1(int mode,float v);
void moto_mov2(int mode,float v);

void moto_go1(float v,float dead);
void moto_go2(float v,float dead);

void moto_stop(void);

#endif
