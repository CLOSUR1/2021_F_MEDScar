#include "encoder.h"  
#include "math.h"
#include "string.h"
#include "syslib.h"

ENCODER encoder;
ROLL_SIZE roll_size;

void Encoder_TIM2_TIM4_TIM9_Init(u16 TT) 
{
	roll_size.deta_t=TT;
	roll_size.pp_l=540;//1040���� 
	roll_size.pp_r=540;//1040���� 
	roll_size.r=3.45f;  //��̥�뾶2.25cm
	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
	Encoder_Reset();
	
  TIM9_encoder_NV(TT);	
}

void Renew_Encoder(void)
{
	encoder.int_v2=ENCODER_INIT_CNT-TIM4->CNT; //????
	encoder.int_v2*=MOTO2_ENCODER_DIR;
	
	TIM4->CNT=ENCODER_INIT_CNT ;
	
	encoder.int_x2+=encoder.int_v2;
	
	encoder.v2=encoder.int_v2/roll_size.pp_l*2000*3.1415926f*roll_size.r/roll_size.deta_t;
	encoder.x2=2*3.1415926f*roll_size.r*encoder.int_x2/roll_size.pp_l;
////////////////////////////////////
	encoder.int_v4=ENCODER_INIT_CNT-TIM2->CNT; //????
	encoder.int_v4*=MOTO4_ENCODER_DIR;
	
	TIM2->CNT=ENCODER_INIT_CNT ;

	encoder.int_x4+=encoder.int_v4;
	
	encoder.v4=(2*3.1415926f*roll_size.r*encoder.int_x4/roll_size.pp_r-encoder.x4)/roll_size.deta_t*2000;
	
	//encoder.v4=encoder.int_v4/roll_size.pp_r*2000*3.1415926f*roll_size.r/roll_size.deta_t;
	encoder.x4=2*3.1415926f*roll_size.r*encoder.int_x4/roll_size.pp_r;
}

void Encoder_Reset(void)
{
	memset(&encoder,0,sizeof(encoder));
	TIM2->CNT=ENCODER_INIT_CNT ;
	TIM4->CNT=ENCODER_INIT_CNT ;
}

float angle2x(float angle,float len)
{
	return angle*3.1415926f/180*len/2;
}

float lowpass_filter(float target,float cx,float c)
{
	return target*c+cx*(1-c);
}

void TIM1_BRK_TIM9_IRQHandler(void)   //TIM9????
{
   if(TIM_GetITStatus(TIM9,TIM_IT_Update)!=RESET)
      {
				TIM_ClearITPendingBit(TIM9,TIM_IT_Update); 
        /////////////////////////////
			   Renew_Encoder();
				////////////////////////////
      }

}

void TIM9_encoder_NV(u16 TT)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = TT*10-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =SYSCLK*100-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn ;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIMx					 
}

void Encoder_TIM2_Init(void)
{
    GPIO_InitTypeDef         GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef        TIM_ICInitStructure;
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//??GPIOA??  
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);//PA0????
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);//PA1????
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //GPIOA0,GPIOA1
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA,&GPIO_InitStructure); 
 
    TIM_TimeBaseStructure.TIM_Period = 65535; //??????????????????????????
    TIM_TimeBaseStructure.TIM_Prescaler = 0; //??????TIMx???????????  ???
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //??????:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
 
    //???????????   IT1  IT2??????????????</span>
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising );
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;  //?????
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //???????
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //??????
    TIM2->CNT = ENCODER_INIT_CNT ;
    TIM_Cmd(TIM2, ENABLE);  //??TIM3
}


void Encoder_TIM4_Init(void)
{ 
    GPIO_InitTypeDef         GPIO_InitStructure; 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef        TIM_ICInitStructure;
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//??TIM3??
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//??GPIOB??
  
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);//PB0????
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4);//PB1????
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //GPIOB0,GPIOB1
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
    GPIO_Init(GPIOB,&GPIO_InitStructure); 
 
    TIM_TimeBaseStructure.TIM_Period = 65535; //??????????????????????????
    TIM_TimeBaseStructure.TIM_Prescaler = 0; //??????TIMx???????????  ???
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //??????:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM??????
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising );

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;  //?????
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //???????
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //??????
    TIM4->CNT = ENCODER_INIT_CNT ;
    TIM_Cmd(TIM4, ENABLE);  //??TIM3

}
