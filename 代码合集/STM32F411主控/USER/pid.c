#include "pid.h"
#include "syslib.h"

int pid_work(PID *pid, float target, float cx)
{
	
	  pid->cx=(1-pid->c)*cx+pid->c*pid->cx;
	
    pid->e[2]=pid->e[1];	//误差迭代
    pid->e[1]=pid->e[0];
    pid->e[0]=target-cx;

    if(!pid->mode)
        pid->intg+= pid->e[0];

    if(pid->mode)
    {
        pid->deta_u=pid->kp*(pid->e[0]-pid->e[1])+
                    pid->ki*pid->e[0]-
                    pid->kd*(pid->e[0]-2*pid->e[1]+pid->e[2]);
        pid->output+=pid->deta_u;
    }
    else
        pid->output=pid->kp*pid->e[0]+
                    pid->ki*pid->intg-
                    pid->kd*(pid->e[0]-pid->e[1]);

    if (pid->max||pid->min)//输出限幅
    {
        if (pid->output>pid->max)
							pid->output=pid->max;
        if (pid->output<pid->min)
							pid->output=pid->min;
    }

    if (absf(pid->e[0]-pid->e[1])<0.001f&&absf(pid->e[0])<0.5f)//更新完成标志位
		{
			pid->finish_count++;
			if(pid->finish_count>30)
					pid->finish = 1;
		}
		else
		{
			pid->finish_count=0;
			pid->finish = 0;
		}
		
		if(pid->watch_dog==0)//定时复位数
				pid->watch_dog=450;
				
		
		if(pid->watch_count>pid->watch_dog)
				pid->finish=1;
		
		pid->watch_count++;
		
		return pid->finish;
}

void pid_init(PID *pid,int mode,float target,float cx,float kp,float ki,float kd)
{
    pid->mode=mode;
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;
    pid->target=target;
    pid->cx=cx;

    pid_work(pid, target, cx);
}

void pid_init3(PID *pid0)
{
	pid_work(pid0, pid0->target, pid0->cx);
}

void pid_reset(PID *pid)
{
    memset(pid,0,sizeof(*pid));
}

int pid_watch_dog(PID *pid,int watch_dog)
{
	if(pid->watch_count>=watch_dog)
	{
		 pid_reset(pid);
		 pid->watch_count=watch_dog;
		 return 1;
	}
	else
	{
		pid->watch_count++;
		return 0;
	}
}

void pid_print(PID pid,int chal)
{
    printf("%f",pid.e[0]);
}
