#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 



#define USART_REC_LEN2 		50  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF2[USART_REC_LEN2]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;     

void uart2_init(u32 bound);
extern float u2[3];
extern int UNUM1;
extern int UNUM2;
extern int NNUM;
extern int LEN1;
extern int LEN2;

extern int u2_succrec_count;
#endif


