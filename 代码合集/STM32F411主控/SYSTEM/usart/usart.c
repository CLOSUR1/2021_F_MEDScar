#include "usart.h"	
#include "syslib.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
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
u8 USART_RX_BUF1[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART1_RX_STA=0;  

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{

//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
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


void USART1_IRQHandler(void)                	//串口1中断服务程序
{

		u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
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
	

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{

//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
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
//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
///////////////
//		
//		u8 Res;
//		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
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
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
// } 	
//}

void uart_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}


