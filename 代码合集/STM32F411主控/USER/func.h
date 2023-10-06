#ifndef  _FUNC_H
#define  _FUNC_H

#include "pid.h"

#define GO 0 //ǰ��
#define TURN 1 //ת��
#define PUT 2  //ҩ����
#define TARGET 3 // ���Ŀ������
#define NUM1 4 //����ж�����
#define NUM2 5 //���Զ������
#define XUN 6 //λ�ý���
#define GO2 7
#define DELAY 8
#define MOV 9
#define SIG 10
#define WIFI_TARGET 11

extern int N[8],N1[8],N2[8];

extern int MAX_SPEED;
extern float TURN_RADIUS_L;
extern float TURN_RADIUS_R;
extern int TARGET_NUM;
int target_num(void);
extern int NUM_FLAG;
extern int NUMBER[8];

int find_num1(int value);
int find_num2(int value);
int wifi_target_num(void);

int FUNC(int mode,int value);
void RESET_ALL(void);

void test(void);

int mov(float v2,float v4);
void mov_reset(void);


int go(float x2,float x4,float v2,float v4);
void go_reset(void);

int turn(float angle); //ת��
void turn_reset(void);

int xgo(float x); //Ѳ��ǰ��
void xgo_reset(void);

int xun(float a); //λ�ý���
void xun_reset(void);

extern int XUN_MIDDLE_VALUE;

int xmov(void);
void xmov_reset(void);
void head(void);

extern int ack_flag;

#endif
