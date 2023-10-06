#include "usart2.h"
#include "sys.h"
#include "uart_parse.h"
#include "led.h"

 
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	

u8 USART_RX_BUF2[USART_REC_LEN2];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART2_RX_STA=0;       //����״̬���	


void uart2_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx ;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
//	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	
}

int uart2_res_flag=0;
float u2[3];
//float u2_pre[3];
//int u2_succrec_count;

int LED_COUNT;

int UNUM1,UNUM2,NNUM,LEN1,LEN2;
int u21;

void USART2_IRQHandler(void)                	//����1�жϷ������
	{
		
  	u8 Res;
		
//		GLED=RLED;
//		RLED=~RLED;
		
		LED_COUNT++;
		if(LED_COUNT>10)
			LED=~LED,LED_COUNT=0;
		
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
		{
			Res = USART_ReceiveData(USART2);
			if(Res=='&')
				uart2_res_flag=1;
			if(uart2_res_flag==1)
		  	USART_RX_BUF2[USART2_RX_STA++] = Res;  		 
			if(uart2_res_flag==1&&Res=='*')
			{
				sbz_parse((char*)USART_RX_BUF2,u2,USART2_RX_STA,3);
				uart2_res_flag=0;
				USART2_RX_STA=0;		

				u21=u2[0];  //��ʼ��������
				LEN2=u21%10;
				u21=(u21-LEN2)/10;
				LEN1=u21%10;
				u21=(u21-LEN1)/10;
				NNUM=u21%10;
				u21=(u21-NNUM)/10;
				UNUM2=u21%10;
				u21=(u21-UNUM2)/10;
				UNUM1=u21%10;
			}	 
		}		

 } 
	
 
