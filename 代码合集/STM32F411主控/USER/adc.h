#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 

void ADC15_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  

float ADC15_getu(u8 times);
int HEAVY(void);

//extern float DRUGZ_TEST_VOL;
//extern int HEAVY_FLAG;
//void PUT_TEST(void);

#endif 















