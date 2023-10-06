#include "func.h"
#include "syslib.h"


int FUNC(int mode,int value) //进程调度函数
{
	target_step++;
	
	if(STEP==target_step)
	{
			switch(mode)
			{
				case GO:
					if(xgo(value)) //巡线前进
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case TURN:     //转向
					if(turn(value))
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case PUT: //检测药物
				PUT_TEST_FLAG=1;
				PUT_TARGET=value;
				if(PUT_FLAG==value)
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case TARGET: //识别目标数字
					if(target_num()&&TARGET_NUM!=0)
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case NUM1:  //识别1个数字
					if(find_num1(value))
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case NUM2:  //识别2个数字
					if(find_num2(value))
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case XUN: //对准红线矫正
					if(xun(value))
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case GO2:
					if(go(value,value,MAX_SPEED,MAX_SPEED))
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
					
				case MOV: 
					if(xmov())
					{
						RESET_ALL();
						STEP++;
						return 1;
					}
					else
						return 0;
				case SIG: //从机接收主机信号
					if(u1[0]==1)
					{
						RESET_ALL();
						STEP++;
						u1[0]=0;
						return 1;
					}
					else
						return 0;
				
				case WIFI_TARGET: //从机接收主机信号
					if(wifi_target_num())
					{
						RESET_ALL();
						STEP++;
						u1[0]=0;
						return 1;
					}
					else
						return 0;
					
				default:
					return 0;
			}
	}
	else
		return 0;
}


void RESET_ALL(void)
{
	PUT_TEST_FLAG=0;
	PUT_FLAG=2;
	PUT_TARGET=2;
	memset(N,0,8*sizeof(int));
	memset(N1,0,8*sizeof(int));
	memset(N2,0,8*sizeof(int));
	NUM_FLAG=1;
	go_reset();
	mov_reset();
	xgo_reset();
	xun_reset();
}


int TARGET_NUM=0;
int NUM_FLAG=0;

int newT=1;
int N[8];

int sum(int a[])
{
	int s=a[0];
	for(int i=1;i<8;i++)
		s+=a[i];
	return s;
}

int maxlist(int a[])
{
	int max=a[0],maxi=0;
	for(int i=1;i<8;i++)
		if(a[i]>max) max=a[i],maxi=i;
	return maxi;
}

int target_num(void)
{
	if(NNUM!=1||UNUM1==0) return 0;
	
	int h=UNUM1-1;
	N[h]++;
	
	if(sum(N)>80) 
	{
		TARGET_NUM=maxlist(N)+1;
		return 1;
	}
	else return 0;
}

int NUMBER[8];

int find_num1(int value)
{
		return 1;
}

int N1[8],N2[8];

int find_num2(int value)
{
	if(NNUM!=2||UNUM1==0||UNUM2==0) return 0;
	
	int h1=UNUM1-1,h2=UNUM2-1;
	N1[h1]++;
	N2[h2]++;
	
	if(sum(N1)>80) 
	{
		NUMBER[value-1]=maxlist(N1)+1;
		NUMBER[value]=maxlist(N2)+1;
		return 1;
	}
	else return 0;
}

int wifi_target_num(void)
{
	if(u1[0]>=1&&u1[0]<=8) 
		{
			TARGET_NUM=u1[0];
			return 1;
		}
	else return 0;
}


void test(void)
{
	moto_go1(-30,0);
	moto_go2(30,0);
	printstr("encoder:");
	printfloat(encoder.int_x2);
	printfloat(encoder.int_x4);
	
	printstr("ADC:");
	printfloat(ADC15_getu(1));

	printstr("k210:");
	printarray(u2,2);
	
	printstr("openmv:");
	printarray(u6,2);
	
	printstr("    ");
}


int XUN_MIDDLE_VALUE;
float MOTO2=50;
float MOTO4=50;
	
PID pid_mov_v2;
PID pid_mov_v4;

int mov(float v2,float v4)
{
	pid_mov_v2.kp=3;
	pid_mov_v2.ki=1;
	pid_mov_v2.kd=0;
	pid_mov_v2.max=100-MOTO2;
	pid_mov_v2.min=-100+MOTO2;
	pid_mov_v2.target=v2;         
	pid_mov_v2.cx=encoder.int_v2;

	
	pid_mov_v4.kp=3;
	pid_mov_v4.ki=1;
	pid_mov_v4.kd=0;
	pid_mov_v4.max=100-MOTO4;
	pid_mov_v4.min=-100+MOTO4;
	pid_mov_v4.target=v4;
	pid_mov_v4.cx=encoder.int_v4;
	
	
	pid_init3(&pid_mov_v2);
	pid_init3(&pid_mov_v4);
	
	moto_go1(pid_mov_v2.output,MOTO2);
	moto_go2(pid_mov_v4.output,MOTO4);
	
 //printf("%f\r\n",pid_mov_v4.output);

	return pid_mov_v2.finish & pid_mov_v4.finish;
}

int MAX_SPEED;

void mov_reset(void)
{
	Encoder_Reset();
	pid_reset(&pid_mov_v2);
	pid_reset(&pid_mov_v4);
}

PID pid_go_x2;
PID pid_go_x4;

int go(float x2,float x4,float v2,float v4)
{
	pid_go_x2.kp=0.7;
	pid_go_x2.max=v2;
	pid_go_x2.min=-v2;
	pid_go_x2.target=x2;         
	pid_go_x2.cx=encoder.x2;
	
	pid_go_x4.kp=0.7;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ;
	pid_go_x4.max=v4;
	pid_go_x4.min=-v4;
	pid_go_x4.target=x4;
	pid_go_x4.cx=encoder.x4;

	pid_go_x2.watch_dog=x2>0?x2*8:(-x2)*8;
	pid_go_x4.watch_dog=x2>0?x2*8:(-x2)*8;

	pid_init3(&pid_go_x2);
	pid_init3(&pid_go_x4);
	
	mov(pid_go_x2.output,pid_go_x4.output);
	
//	printfloat(pid_go_x2.e[0]);

	return pid_go_x2.finish & pid_go_x4.finish;
}


void go_reset(void)
{
	mov_reset();
	pid_reset(&pid_go_x2);
	pid_reset(&pid_go_x4);
}

float TURN_RADIUS_L;
float TURN_RADIUS_R;
int turn(float angle)
{
	float r;
	if(absf(angle)<=90) r=10.0f;
	else r=10.0f;
	
	float x=angle/90.0f* r;
	return go(x,-x,MAX_SPEED,MAX_SPEED);
}

void turn_reset(void)
{
	go_reset();
	xgo_reset();
}


PID pid_xgo;
PID pid_xmov;


int enstop=0;
int xgo(float x)
{
	
	pid_xmov.kp=5                                                                                                                                     ;
	pid_xmov.kd=0;
	pid_xmov.max=20;
	pid_xmov.min=-20;
	pid_xmov.target=XUN_MIDDLE_VALUE;
	pid_xmov.cx=u2[1];

	pid_init3(&pid_xmov);
	
	pid_xgo.kp=0.25;
	pid_xgo.kd=0;
	pid_xgo.max=MAX_SPEED;
	pid_xgo.min=-MAX_SPEED;
	pid_xgo.target=pid_xmov.output;
	pid_xgo.cx=u2[2];
		
	pid_init3(&pid_xgo);
	
	if(LEN1>6 && x==1 && encoder.x2>10) enstop=1;  //LEN1停车
	if(LEN2>3 && x==2 && encoder.x2>3) enstop=1;  //LEN2停车
	if(LEN1==0 && x==3 && encoder.x2>30) enstop=1;//停车结束
	if(LEN1>6 && x==4 && encoder.x2>60) enstop=1; //中端停车
	if(LEN1>6 && x==5) enstop=1; //倒车矫正
	if(LEN2>3 && x==6 && encoder.x2>50) enstop=1; 
	if(enstop==0)
	{
		if(x==5)
		{
			mov(-1, -1);
		}
		else
		{
			if(pid_xgo.output>0)  mov(MAX_SPEED, MAX_SPEED+pid_xgo.output);
			if(pid_xgo.output<=0) mov(MAX_SPEED-pid_xgo.output, MAX_SPEED);
		}
	}
	else
	{
		float v=(float)encoder.int_v2*0.875f;
		mov(v,v);
//		mov(0,0);
	}
	
	if(enstop==1&&encoder.int_v2==0&&encoder.int_v4==0) return 1;
	else return 0;

}

void xgo_reset(void)
{
	enstop=0;
	moto_stop();
	u2[2]=0;
	u2[1]=0;
	go_reset();
	pid_reset(&pid_xgo);
	pid_reset(&pid_xmov);
}

PID pid_xun_k;
PID pid_xun_r;
int xun(float a)
{
	pid_xun_k.kp=2;
	pid_xun_k.target=XUN_MIDDLE_VALUE;
	pid_xun_k.cx=u2[1];
	pid_xun_k.watch_dog=25;

	pid_xun_r.kp=-1;
	pid_xun_r.target=XUN_MIDDLE_VALUE;
	pid_xun_r.cx=u2[2];
	pid_xun_r.watch_dog=25;
	
	pid_init3(&pid_xun_k);

//	go(-pid_xun_k.output,pid_xun_k.output,5,5);
	
	if(pid_xun_k.watch_count>pid_xun_k.watch_dog) return 1;
	else return 0;
}

void xun_reset(void)
{
	pid_reset(&pid_xun_r);
	pid_reset(&pid_xun_k);
	xgo_reset();
}


int xmov(void)
{

		return 0;
}

void xmov_reset(void)
{
	xgo_reset();
}

int ack_flag=0;
void Affair_Callback(void)
{
	
}
