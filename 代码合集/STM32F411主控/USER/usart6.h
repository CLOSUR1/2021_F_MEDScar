#ifndef __USART6_H
#define __USART6_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 


#define USART_REC_LEN6 			100  	//�����������ֽ��� 200
#define EN_USART6_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	

void uart6_init(u32 bound);
extern float u6[3];
//extern int U6COUNT;
#endif


