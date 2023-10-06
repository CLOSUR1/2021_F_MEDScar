#include "usart.h"	
#include "syslib.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{   
	  USART_SendData(USART1,(unsigned char) ch);
	  while (!(USART1->SR & USART_FLAG_TXE)); 
//	
//		USART_SendData(USART2,(unsigned char) ch);
//	  while (!(USART2->SR & USART_FLAG_TXE)); 
	
//		  USART_SendData(USART6,(unsigned char) ch);
//	  while (!(USART6->SR & USART_FLAG_TXE)); 
	
		return ch;
}

#endif

int uart1_res_flag=0;
float u1[2];
u8 USART_RX_BUF1[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART1_RX_STA=0;  

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{

//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//				Res = USART_ReceiveData(USART1);
//			if(Res==':')
//					uart1_res_flag=1;
//				if(uart1_res_flag==1)
//					USART_RX_BUF1[USART1_RX_STA++] = Res;  		 
//				if(uart1_res_flag==1&& WIFI_REMOTE_TEST(USART_RX_BUF1,USART1_RX_STA))
//				{ 		
//					WIFI_Remote_Mode=USART_RX_BUF1[4]-48;
//					uart1_res_flag=0;
//					USART1_RX_STA=0;				
//				}					
//			} 	
//}
//	


void USART1_IRQHandler(void)                	//����1�жϷ������
{

		u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res = USART_ReceiveData(USART1);
			if(Res=='&')
				uart1_res_flag=1;
			if(uart1_res_flag==1)
		  	USART_RX_BUF1[USART1_RX_STA++] = Res;  		 
			if(uart1_res_flag==1&&Res=='*')
			{ 		
    		sbz_parse((char*)USART_RX_BUF1,u1,USART1_RX_STA,2);
				uart1_res_flag=0;
				USART1_RX_STA=0;				
		//		printarray(u1,10);
		  }		
		
    } 	
}
	

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{

//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//				Res = USART_ReceiveData(USART1);
//				if(Res=='[')
//					uart1_res_flag=1;
//				if(uart1_res_flag==1)
//					USART_RX_BUF1[USART1_RX_STA++] = Res;  		 
//				if(uart1_res_flag==1&&Res==']')
//				{ 		
//					sbz_parse_new((char*)USART_RX_BUF1,u1);
//					uart1_res_flag=0;
//					USART1_RX_STA=0;				
//			//		printarray(u1,10);
////					WIFI_SendData(USART_RX_BUF1);
//				}					
//			} 	
//}
//	


//int FAR_FLAG=1;
//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
///////////////
//		
//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//			Res = USART_ReceiveData(USART1);
//			if(Res=='d')
//				uart1_res_flag=1;
//			if(uart1_res_flag==1)
//		  	USART_RX_BUF1[USART1_RX_STA++] = Res;  		 
//			if(uart1_res_flag==1&&Res=='m')
//			{ 		
//    		VL53L0_parse((char*)USART_RX_BUF1,u1);
//				
//				if(u1[0]>200&&u1[0]<250)
//					FAR_FLAG=0,u1[0]=0;
//				else
//					FAR_FLAG=1,u1[0]=0;
//				
//				uart1_res_flag=0;
//				USART1_RX_STA=0;				
////				printarray(u1,10);
//		  }		
//			
//////////////
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
// } 	
//}

void uart_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
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
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}


