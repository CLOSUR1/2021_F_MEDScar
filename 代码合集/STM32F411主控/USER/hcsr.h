#ifndef __HCSR_H
#define __HCSR_H
#include "sys.h"

void TIM11_IRQ_Init(float TT);
int HCSR_GetDis(void);
void HCSR_Init(void);
extern int PUT_TEST_FLAG;
extern int PUT_FLAG;
void PUT_TEST(void);
extern int PUT_TARGET;
void HCSR_TEST(void);
void HW_Init(void);
void PUT_TEST_HW(void);
#endif 
