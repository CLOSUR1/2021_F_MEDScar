#include "syslib.h"



int main(void)
{ 
 
	delay_init(100);		  //��ʼ����ʱ����
	
	MOTO2_TIM3_A4950_Init(1);//TIM3 PB 0 1 4 5 ; �������PWM��ʼ����PWMƵ��5KHZ
	
	uart_init(115200); 		//TX PA9 RX PA10 Ԥ������/WIFI
//	WIFI_Init();
	uart2_init(9600); 	//PA2 PA3 OPENMV`
//  uart6_init(115200); //PA11 PA12 ������
	
	RGBLED_Init();  //G PB12  R PB13 ָʾ��
  LED_Init();
	
	HW_Init(); //����ҩ���� ECHO PA5
	Encoder_TIM2_TIM4_TIM9_Init(10); //TIM2 PA0 PA1  TIM4 PB6 PB7 ��������ʼ��
	
  TIM10_IRQ_Init(15);  //���ж� 20ms�ж�1��
			
	while(1)
	{
		MAX_SPEED=5;      	 //С������ٶ�����
		MODE=HOST;           //����С����ɫ��������ӻ�  HOST/SLAVE
    PUT_TEST_HW();       //ҩ����ü�⣬��ʹ��delay���Ž��ж�
		LED=~LED;
		
		delay_ms(500);
	}
	
}



	
