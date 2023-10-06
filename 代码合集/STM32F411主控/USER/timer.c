#include "timer.h"
#include "syslib.h"




void TIM10_IRQ_CallBack(void)
{	
		if(u6[0]>300&&u6[0]<350) //如果距离在30cm到35cm之间，则判定存在障碍物
			mov(0,0),WIFI_FLAG=3;
		else
			OS();
}










void TIM1_UP_TIM10_IRQHandler(void)   //TIM7中断
{
	if (TIM_GetITStatus(TIM10, TIM_IT_Update) != RESET)  
		{
		  TIM_ClearITPendingBit(TIM10, TIM_IT_Update); 	
/////////
//      Renew_Encoder();			
			TIM10_IRQ_CallBack();			
/////////
	  }
}


void TIM10_IRQ_Init(u16 TT)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = TT*10-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =SYSCLK*100-1; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM10, ENABLE);  //使能TIMx					 
}


