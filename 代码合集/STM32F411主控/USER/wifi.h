#ifndef  _WIFI_H
#define  _WIFI_H

#include "sys.h"

void WIFI_Init(void);
void WIFI_SendData(float data);
void WIFI_Report(void);
extern int WIFI_FLAG;
void WIFI_Report(void);
void WIFI_SendStr(char *str);
extern int WIFI_Remote_Mode;
int WIFI_REMOTE_TEST(u8 *buf,int len);

#define REMOTE_TURN_LEFT 4
#define REMOTE_TURN_RIGHT 8
#define REMOTE_GO_AHEAD 1
#define REMOTE_GO_BACK 2
#define REMOTE_START_STOP 16

extern int WIFI_Remote_Enable;
void WIFI_Remote_Control(void);

#endif
