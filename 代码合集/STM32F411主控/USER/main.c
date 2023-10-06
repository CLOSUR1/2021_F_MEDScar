#include "syslib.h"



int main(void)
{ 
 
	delay_init(100);		  //初始化延时函数
	
	MOTO2_TIM3_A4950_Init(1);//TIM3 PB 0 1 4 5 ; 电机驱动PWM初始化，PWM频率5KHZ
	
	uart_init(115200); 		//TX PA9 RX PA10 预留蓝牙/WIFI
//	WIFI_Init();
	uart2_init(9600); 	//PA2 PA3 OPENMV`
//  uart6_init(115200); //PA11 PA12 激光测距
	
	RGBLED_Init();  //G PB12  R PB13 指示灯
  LED_Init();
	
	HW_Init(); //红外药物检测 ECHO PA5
	Encoder_TIM2_TIM4_TIM9_Init(10); //TIM2 PA0 PA1  TIM4 PB6 PB7 编码器初始化
	
  TIM10_IRQ_Init(15);  //主中断 20ms中断1次
			
	while(1)
	{
		MAX_SPEED=5;      	 //小车最大速度限制
		MODE=HOST;           //设置小车角色，主机或从机  HOST/SLAVE
    PUT_TEST_HW();       //药物放置检测，有使用delay不放进中断
		LED=~LED;
		
		delay_ms(500);
	}
	
}



	
