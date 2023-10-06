#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "sys.h" 

void Read_Speed(u8 cha);
void Speed_Clear(void);

void Encoder_TIM2_Init(void);
void Encoder_TIM4_Init(void);

typedef struct
{
	int int_a2;
	int int_x2;
	int int_v2;
	
	int int_a4;
	int int_x4;
	int int_v4;
	
	int circle2,circle4;
	float a2,v2,x2;
	float a4,v4,x4;
	
	float r,pulse_percircle;
	
}ENCODER;

typedef struct 
{
	float r;
	float pp_l;
	float pp_r;
	u16 deta_t;
	
}ROLL_SIZE;

#define ENCODER_INIT_CNT 30000

extern ENCODER encoder;

void TIM9_encoder_NV(u16 TT);

void Encoder_TIM2_TIM4_TIM9_Init(u16 TT);
void Renew_Encoder(void);
float angle2x(float angle,float len);
void Encoder_Reset(void);

float lowpass_filter(float target,float cx,float c);
//extern float RIGHT_CORRECT;
//extern float LEFT_CORRECT;

//extern float RIGHT_CORRECT_P;
//extern float LEFT_CORRECT_P;
//extern float RIGHT_CORRECT_N;
//extern float LEFT_CORRECT_N;
#endif
