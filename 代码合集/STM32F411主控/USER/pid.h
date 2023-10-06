#ifndef __PID_H
#define __PID_H

#include "string.h"

typedef struct 
{
    float kp,ki,kd;
    float mode;

    float e[3],intg;
    float target;
    float cx;

    float deta_u,output;
    float max,min;

    int finish;
	  int finish_count;
	  int watch_dog;
		int watch_count;
    int c;
	
}PID;

typedef struct 
{
    float kp,ki,kd;
    float mode;

    float max,min;
}PID_BASE;

int pid_work(PID *pid, float target, float cx);
void pid_init(PID *pid, int mode, float target, float cx, float kp, float ki, float kd);
void pid_reset(PID* pid);
int pid_watch_dog(PID *pid,int watch_dog);
void pid_print(PID pid,int chal);
void pid_init3(PID *pid0);


#define absf(a) (a>0?a:-a)
#define RESET(a) (memset(&a,0,sizeof(a)))
	
#endif 
