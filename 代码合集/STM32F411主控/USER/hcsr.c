#include "hcsr.h"
#include "syslib.h"

#define TRIG PBout(8)
#define ECHO PAin(5)

void HW_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;			
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_5;			
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;				
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_DOWN;		
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

void PUT_TEST_HW(void)
{
	int count1=0;
	int n=3;
	if(PUT_TEST_FLAG==1)
	{
		for (int i=0;i<n;i++)
		{
			if(ECHO==1) count1++;
//			printfloat(ECHO);
			delay_ms(100);
		}
	
		if(PUT_TARGET==1)
		{
			if(count1==n) PUT_FLAG=1;
		}
		
		if(PUT_TARGET==0)
		{
			if(count1==0) PUT_FLAG=0;
		}
	}
	else if(PUT_TEST_FLAG==0)
	{
		PUT_FLAG=2;
	}
}

void HCSR_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_8;			
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;		
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;		
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9;			
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;				
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL;		
	GPIO_Init(GPIOB, &GPIO_InitStruct);	

	TIM11_IRQ_Init(0.1);
}

int HCSR_GetDis(void)
{
	int t = 0;
	int distance;
	int count = 0;
	
	TRIG=0;
	delay_us(5);
	TRIG=1;
	delay_us(10);
	TRIG=0;

	TIM11->CNT = 0;
	
	while( ECHO == 0)
	{
		t++;
//		delay_us(10);
	
		if(t>= 50000*3)
			return 0;
	}

	TIM_Cmd(TIM11, ENABLE);	
	
	t=0;

	while(ECHO== 1)
	{
		t++;
//		delay_us(20);
	
		if(t >= 120000*3)
			return 0;		
	}

	count = TIM11->CNT;
	
	TIM_Cmd(TIM11, DISABLE);	
	
	distance = count/1;

	return distance;

}

int PUT_FLAG=0;
int PUT_TEST_FLAG=0;
int PUT_TARGET=2;
int d[10];

int sq(int a[],int n) //��������⣬����ҩ��ʱ������Ϊ��3���ڲ���������
{
	int sq=0;
	for (int i=0;i<n;i++)
	{
		if(a[0]-a[i]>=-1&&a[0]-a[i]<=1)
			sq++;
	}
	return sq;
}

int K[3];
void PUT_TEST(void)
{
	int n=5;
	if(PUT_TEST_FLAG==1)
	{
		for (int i=0;i<n;i++)
		{
			int len=HCSR_GetDis();
			d[i]=len;
			delay_ms(100);
			printfloat(len);
		}
		
		K[2]=K[1]; //��ѯ�������
		K[1]=K[0];
		K[0]=sq(d,n);

//		printfloat(K[0]);
		if(PUT_TARGET==1)
		{
			if(K[0]==n&&K[1]==n&&K[2]==n) PUT_FLAG=1;
		}
		
		if(PUT_TARGET==0)
		{
			if(K[0]!=n&&K[1]!=n&&K[2]!=n&&K[0]!=0&&K[1]!=0&&K[2]!=0) PUT_FLAG=0;
		}
	}
	else if(PUT_TEST_FLAG==0)
	{
		PUT_FLAG=2;
		K[2]=0;
		K[1]=0;
		K[0]=0;
	}
}

void HCSR_TEST(void)
{
	PUT_TEST_FLAG=1;
	PUT_TEST();
	if(PUT_FLAG==PUT_TARGET){ GLED=PUT_TARGET;PUT_TARGET=~PUT_TARGET;}
}

void TIM11_IRQ_CallBack(void)
{
	
}


void TIM1_TRG_COM_TIM11_IRQHandler(void)   //TIM11�ж�
{
	if (TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)  
		{
		  TIM_ClearITPendingBit(TIM11, TIM_IT_Update); 
			TIM11_IRQ_CallBack();	     
	  }
}

void TIM11_IRQ_Init(float TT)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM11��ʼ��
	TIM_TimeBaseStructure.TIM_Period = TT*1000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =84-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
  TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM11����,��������ж�

	TIM_Cmd(TIM11, DISABLE);  //�ر�TIM11					 
}

