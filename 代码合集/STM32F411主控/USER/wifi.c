#include "wifi.h"
#include "syslib.h"

void wifi_setprint(int t,char *a)
{
	printstr(a);
	delay_ms(t);
}

void WIFI_Init(void)
{
	wifi_setprint(1000,"AT+CWMODE=2");
//  wifi_setprint(1000,"AT+RST");
	wifi_setprint(1000,"AT+CWSAP=\"ESP_WIFI\",\"12345678\",1,3,4,0");
	delay_ms(1000);
	delay_ms(1000);
	wifi_setprint(1000,"AT+CIPMUX=1");
	wifi_setprint(1000,"AT+CIPSERVER=1");
}

void WIFI_SendStr(char *str)
{
	int len=0;
	while(str[len]!='\0') len++;

	char order[40];
	sprintf(order,"AT+CIPSEND=0,%d",len);
	wifi_setprint(500,order);
	wifi_setprint(0,str);
}

void WIFI_SendData(float data)
{
	float d[1]={data};
	WIFI_SendStr(sbz_format(d,1));
}
	
int WIFI_FLAG=0;
void WIFI_Report(void)
{
	if(WIFI_FLAG==1)
	{
		char order[40];
		sprintf(order,"Target number %d has been received",TARGET_NUM);
		WIFI_SendStr(order);
	}
	
	if(WIFI_FLAG==2)
		WIFI_SendStr("The medication has been delivered");
	
	if(WIFI_FLAG==3)
		WIFI_SendStr("The car is blocked by front barrier");
		
	
	WIFI_FLAG=0;
}

int WIFI_Remote_Mode;

int WIFI_REMOTE_TEST(u8 *buf,int len)
{
	if(len<5) return 0;
	if(buf[len-1]=='0'&&buf[len-2]=='0'&&buf[len-3]=='X'&&buf[len-4]=='0')
		return 1;
	else
		return 0;
}

int WIFI_Remote_Enable=0;

void WIFI_Remote_Control(void)
{
	if(WIFI_Remote_Mode==REMOTE_TURN_LEFT)  mov(-3,3);
	if(WIFI_Remote_Mode==REMOTE_TURN_RIGHT) mov(3,-3);
	if(WIFI_Remote_Mode==REMOTE_GO_AHEAD)   mov(5,5);
	if(WIFI_Remote_Mode==REMOTE_GO_BACK)    mov(-5,-5);
}









