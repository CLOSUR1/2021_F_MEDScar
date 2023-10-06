#include "moto2.h"
#include "syslib.h"

int MOTO_MODE;

void MOTO2_TIM3_A4950_Init(int KHZ)
{  
	MOTO_MODE=1;
	
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1;
                           
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //?????
  TIM_TimeBaseInitStructure.TIM_Prescaler = 5*SYSCLK/KHZ-1;   
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInitStructure.TIM_Period = 99 ;    
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
  TIM_Cmd(TIM3,ENABLE);

}


void MOTO2_TIM3_TB6122_Init(int KHZ)
{
	MOTO_MODE=0;
	
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
                           
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_TIM3);
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //?????
  TIM_TimeBaseInitStructure.TIM_Prescaler = 5*SYSCLK/KHZ-1;   
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInitStructure.TIM_Period = 99 ;    
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
  TIM_Cmd(TIM3,ENABLE);
	
	MOTO_IO_Init();
}

void MOTO_IO_Init(void) //PB 0 1 2 10
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_10 | GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_10 | GPIO_Pin_0);
}


void moto_stop(void)
{
if(MOTO_MODE==1)
	{
		if(TIM3->CCR1>TIM3->CCR2)
			{
				TIM3->CCR1=1;
				TIM3->CCR2=1;
			}
			else
			{
				TIM3->CCR2=1;
				TIM3->CCR1=1;
			}
			
		if(TIM3->CCR3>TIM3->CCR4)
			{
				TIM3->CCR3=1;
				TIM3->CCR4=1;
			}
			else
			{
				TIM3->CCR4=1;
				TIM3->CCR3=1;
			}
	}
	else
	{
		PBout(0)=0;
		PBout(1)=0;
		PBout(2)=0;
		PBout(10)=0;	
	}
}

void moto_mov1(int mode,float v)
{
	if(MOTO_MODE==1)
	{
			if(mode==MOTO2_PWM_DIR)
			{
					moto_duty1(1);
					moto_duty2(v);
			}
			else
			{
					moto_duty1(v);
					moto_duty2(1);
			}
	}
	else
	{
		
			if(mode==1)
			{
				PBout(0)=1;
				PBout(1)=0;
			}
			else
			{
				PBout(0)=0;
				PBout(1)=1;
			}
			moto_duty1(v);
	}
}

void moto_mov2(int mode,float v)
{
	if(MOTO_MODE==1)
	{
		if(mode==MOTO4_PWM_DIR)
		{
					moto_duty3(v);
					moto_duty4(1);
				
		}
		else
			{
					moto_duty3(1);
					moto_duty4(v);			
			}
	}

	else
	{
			if(mode==1)
			{
				PBout(2)=1;
				PBout(10)=0;
			}
			else
			{
				PBout(2)=0;
				PBout(10)=1;
			}
			moto_duty2(v);
	}
}

void moto_go1(float v,float dead)
{
	if(v>0)
		moto_mov1(1,v+dead);
	else
		moto_mov1(0,-v+dead);
}

void moto_go2(float v,float dead)
{
	if(v>0)
		moto_mov2(1,v+dead);
	else
		moto_mov2(0,-v+dead);
}


void moto_duty1(float duty)//舵机按占空比操作(Duty:0-100)
{ 
	TIM_SetCompare1(TIM3,duty);	
}

void moto_duty2(float duty)//舵机按占空比操作(Duty:0-100)
{ 
  TIM_SetCompare2(TIM3,duty);	
}

void moto_duty3(float duty)//舵机按占空比操作(Duty:0-100)
{ 
  TIM_SetCompare3(TIM3,duty);		
}

void moto_duty4(float duty)//舵机按占空比操作(Duty:0-100)
{ 
  TIM_SetCompare4(TIM3,duty);		
}





