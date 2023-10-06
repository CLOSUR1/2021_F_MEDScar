#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 



#define USART_REC_LEN2 		50  	//�����������ֽ��� 200
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF2[USART_REC_LEN2]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
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


