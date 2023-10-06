#include "usart2.h"
#include "sys.h"
#include "uart_parse.h"
#include "led.h"

 
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	

u8 USART_RX_BUF2[USART_REC_LEN2];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART2_RX_STA=0;       //接收状态标记	


void uart2_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9与GPIOA10
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
	USART_InitStructure.USART_Mode = USART_Mode_Rx ;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口1 
	
//	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	
}

int uart2_res_flag=0;
float u2[3];
//float u2_pre[3];
//int u2_succrec_count;

int LED_COUNT;

int UNUM1,UNUM2,NNUM,LEN1,LEN2;
int u21;

void USART2_IRQHandler(void)                	//串口1中断服务程序
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

				u21=u2[0];  //开始解析数据
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
	
 
