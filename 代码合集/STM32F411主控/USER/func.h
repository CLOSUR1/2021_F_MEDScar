#ifndef  _FUNC_H
#define  _FUNC_H

#include "pid.h"

#define GO 0 //前进
#define TURN 1 //转向
#define PUT 2  //药物检测
#define TARGET 3 // 检测目标数字
#define NUM1 4 //检测中端数字
#define NUM2 5 //检测远端数字
#define XUN 6 //位置矫正
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

int turn(float angle); //转向
void turn_reset(void);

int xgo(float x); //巡线前进
void xgo_reset(void);

int xun(float a); //位置矫正
void xun_reset(void);

extern int XUN_MIDDLE_VALUE;

int xmov(void);
void xmov_reset(void);
void head(void);

extern int ack_flag;

#endif
