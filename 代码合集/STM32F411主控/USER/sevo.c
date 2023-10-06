#include "sevo.h"
#include "delay.h"


void SEVO_TIM1_Init(void) //PA8 sevo
{  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8  ;
                           
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
 
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //?????
  TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;   
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInitStructure.TIM_Period = 19999 ;    
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
  TIM_OC1Init(TIM1,&TIM_OCInitStructure);
 
  TIM_Cmd(TIM1,ENABLE);
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
						  
   
}


void sevo_ms(float ms) //SEVO1舵机按高电平时间操作
{
	TIM_SetCompare1(TIM1,1000*ms);	  
}



 void sevo_zkb(float zkb)//舵机按占空比操作
{ 
	TIM_SetCompare1(TIM1,(zkb/100)*20*1000);	 	  	
}


void sevo_angle(float angle)//指定舵机转到角度
{ 
	  TIM_SetCompare1(TIM1,(angle+45)/0.09f);	  
	
}



