#ifndef __sevo_H
#define __sevo_H
#include "sys.h"



void SEVO_TIM1_Init(void); //PA8 sevo1,PA11 sevo2

void sevo_ms(float ms);
void sevo_zkb(float zkb);
void sevo_angle(float angle);


#endif
