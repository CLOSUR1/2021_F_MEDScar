#include "mission.h"
#include "syslib.h"

int STEP;
int target_step=-1;

int END(void)	//任务结束复位函数
{
	target_step++;//目标进程序号加1
	if(target_step==STEP)//如果目标进程号等于本进程号
	{
		GLED=1;
		target_step=-1;//目标进程号复位
		STEP=0;//本进程号复位
		RESET_ALL();	//复位PID控制器
		TARGET_NUM=0;	//清零目标数字
		u1[0]=0;
		memset(NUMBER,0,sizeof(NUMBER));//清零识别数字缓存数组
		return 1;//返回进程完成标志位
	}
	return 0;
}


void host(void) //主机程序
{	
  if(FUNC(TARGET,0)) GLED=0,WIFI_FLAG=1; //检测目标数字
  FUNC(PUT,1);  //检测药物
  
	if(TARGET_NUM==1)
	{
		FUNC(GO,2);             FUNC(XUN,0); //前进到LEN2==0
		FUNC(TURN,-90);         FUNC(XUN,0); //右转90度
		if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;  FUNC(XUN,0); //前进到LEN1==0
		if(FUNC(PUT,0)) RLED=0;              //检测药物被取走
		FUNC(TURN,180);					FUNC(XUN,0); //右转180度
		FUNC(GO,2);							FUNC(XUN,0); //前进到LEN2=0
		FUNC(TURN,90);					FUNC(XUN,0); 
		if(FUNC(GO,3)) GLED=1; FUNC(XUN,0);  //前进到LEN1==0
		FUNC(TURN,180);					FUNC(XUN,0);	
	}

	else if(TARGET_NUM==2)
	{
		FUNC(GO,2);             FUNC(XUN,0);
		FUNC(TURN,90);          FUNC(XUN,0);
		if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;  FUNC(XUN,0);
		if(FUNC(PUT,0)) RLED=0;
		FUNC(TURN,180);					FUNC(XUN,0);
		FUNC(GO,2);							FUNC(XUN,0);
		FUNC(TURN,-90);					FUNC(XUN,0);
		if(FUNC(GO,3)) GLED=1; FUNC(XUN,0);
		FUNC(TURN,180);					FUNC(XUN,0);	
	}
	
	else //中端开始
	{	
		FUNC(GO,4); FUNC(XUN,0);  //前进到中端LEN1满
		FUNC(GO,5); FUNC(XUN,0);  //倒退对正数字
		FUNC(NUM2,1);             //识别2个数字
		
		if(TARGET_NUM==NUMBER[0])
		{
			FUNC(GO,2); 					FUNC(XUN,0);
			FUNC(TURN,-90);				FUNC(XUN,0);
			if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;						FUNC(XUN,0);
			if(FUNC(PUT,0)) RLED=0,printfloat(1);
			FUNC(TURN,180);				FUNC(XUN,0);
			FUNC(GO,2);						FUNC(XUN,0);
			FUNC(TURN,90);				FUNC(XUN,0);
			if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
			FUNC(TURN,180);				FUNC(XUN,0);	
		}
		else if(TARGET_NUM==NUMBER[1])
		{
			FUNC(GO,2); FUNC(XUN,0);
			FUNC(TURN,90);FUNC(XUN,0);
			if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;FUNC(XUN,0);
			if(FUNC(PUT,0)) RLED=0,printfloat(1);
			FUNC(TURN,180);				FUNC(XUN,0);
			FUNC(GO,2);						FUNC(XUN,0);
			FUNC(TURN,-90);				FUNC(XUN,0);
			if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
			FUNC(TURN,180);				FUNC(XUN,0);	
		}
		else//远端开始
		{
			FUNC(GO,6);  //略过1个的LEN2停车
			FUNC(TURN,-90);       FUNC(XUN,0);
			FUNC(GO,1);           FUNC(XUN,0);
			FUNC(GO,5);           FUNC(XUN,0);
			FUNC(NUM2,3);
			if(TARGET_NUM==NUMBER[2])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,-90);       FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
				if(FUNC(PUT,0)) RLED=0,printfloat(1);
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(TURN,90);				FUNC(XUN,0);
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,90);        FUNC(XUN,0);
				if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
				FUNC(TURN,180);				FUNC(XUN,0);	
			}
			else if(TARGET_NUM==NUMBER[3])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,90);        FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
				if(FUNC(PUT,0)) RLED=0,printfloat(1);
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(TURN,-90);				FUNC(XUN,0);
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,90);				FUNC(XUN,0);
				if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
				FUNC(TURN,180);				FUNC(XUN,0);	
			}
			else //远端右边开始
			{
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(GO,1);           FUNC(XUN,0);
				FUNC(GO,5);           FUNC(XUN,0);
				FUNC(NUM2,5);
				if(TARGET_NUM==NUMBER[4])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);       FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,90);				FUNC(XUN,0);
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);        FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
			 else if(TARGET_NUM==NUMBER[5])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,90);        FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;         FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,-90);				FUNC(XUN,0);
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);				FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
			}
		}
	}
	
}

void slave(void) //从机程序
{
		FUNC(TARGET,0); 
		FUNC(PUT,1);
		FUNC(GO,2);  					 FUNC(XUN,0);
		FUNC(TURN,90); 				 FUNC(XUN,0);
		if(FUNC(GO,3)) YLED(1);FUNC(XUN,0);
		
		if(FUNC(SIG,1)) YLED(0);
		FUNC(TURN,180); 			 FUNC(XUN,0);
		
		FUNC(SIG,1);
		FUNC(GO,2);   				 FUNC(XUN,0);
		FUNC(TURN,90);				 FUNC(XUN,0);
		FUNC(GO,1);            FUNC(XUN,0);
		FUNC(GO,5);            FUNC(XUN,0);
		FUNC(NUM2,1);
		
			if(TARGET_NUM==NUMBER[0])
		{
			FUNC(GO,2); 					FUNC(XUN,0);
			FUNC(TURN,-90);				FUNC(XUN,0);
			FUNC(GO,3);						FUNC(XUN,0);
			if(FUNC(PUT,0)) RLED=0;
			FUNC(TURN,180);				FUNC(XUN,0);
			FUNC(GO,2);						FUNC(XUN,0);
			FUNC(TURN,90);				FUNC(XUN,0);
			if(FUNC(GO,3)) GLED=1; FUNC(XUN,0);
			FUNC(TURN,180);				FUNC(XUN,0);	
		}
		else if(TARGET_NUM==NUMBER[1])
		{
			FUNC(GO,2); FUNC(XUN,0);
			FUNC(TURN,90);FUNC(XUN,0);
			FUNC(GO,3);FUNC(XUN,0);
			if(FUNC(PUT,0)) RLED=0;
			FUNC(TURN,180);				FUNC(XUN,0);
			FUNC(GO,2);						FUNC(XUN,0);
			FUNC(TURN,-90);				FUNC(XUN,0);
			if(FUNC(GO,3)) GLED=1;FUNC(XUN,0);
			FUNC(TURN,180);				FUNC(XUN,0);	
		}
		else//远端开始
		{
			FUNC(GO,6);  //略过1个的LEN2停车
			FUNC(TURN,-90);       FUNC(XUN,0);
			FUNC(GO,1);           FUNC(XUN,0);
			FUNC(GO,5);           FUNC(XUN,0);
			FUNC(NUM2,3);
			if(TARGET_NUM==NUMBER[2])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,-90);       FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1;FUNC(XUN,0); 

			}
			else if(TARGET_NUM==NUMBER[3])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,90);        FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1;FUNC(XUN,0); 

			}
			else //远端右边开始
			{
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(GO,1);           FUNC(XUN,0);
				FUNC(GO,5);           FUNC(XUN,0);
				FUNC(NUM2,5);
				if(TARGET_NUM==NUMBER[4])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);       FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1;FUNC(XUN,0); 

					}
			 else if(TARGET_NUM==NUMBER[5])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,90);        FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1;FUNC(XUN,0); 
					}
			}
		}
}

int MODE;
void OS(void)
{
	if(MODE==HOST) host();
	else slave();
//	map2();
	END();
	target_step=-1;//进程调度标志位复位

};

void map2(void)
{
			if(FUNC(TARGET,0)) GLED=0; //检测目标数字
			FUNC(PUT,1);  //检测药物
			FUNC(GO,1);           FUNC(XUN,0); //第1级开始
			FUNC(GO,5);           FUNC(XUN,0);
			FUNC(NUM2,1);
			if(TARGET_NUM==NUMBER[0])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,-90);       FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
				if(FUNC(PUT,0)) RLED=0,printfloat(1);
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(TURN,90);				FUNC(XUN,0);
				if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
				FUNC(TURN,180);				FUNC(XUN,0);	
			}
			else if(TARGET_NUM==NUMBER[1])
			{
				FUNC(GO,2);           FUNC(XUN,0);
				FUNC(TURN,90);        FUNC(XUN,0);
				if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
				if(FUNC(PUT,0)) RLED=0,printfloat(1);
				FUNC(TURN,180);				FUNC(XUN,0);
				FUNC(GO,2);						FUNC(XUN,0);
				FUNC(TURN,-90);				FUNC(XUN,0);
				if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
				FUNC(TURN,180);				FUNC(XUN,0);	
			}
			else
			{
					FUNC(GO,1);           FUNC(XUN,0); //第2级开始
					FUNC(GO,5);           FUNC(XUN,0);
					FUNC(NUM2,3);
					if(TARGET_NUM==NUMBER[2])
				{
					FUNC(GO,2);           FUNC(XUN,0);
					FUNC(TURN,-90);       FUNC(XUN,0);
					if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
					if(FUNC(PUT,0)) RLED=0,printfloat(1);
					FUNC(TURN,180);				FUNC(XUN,0);
					FUNC(GO,2);						FUNC(XUN,0);
					FUNC(TURN,90);				FUNC(XUN,0);
					if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
					FUNC(TURN,180);				FUNC(XUN,0);	
				}
				else if(TARGET_NUM==NUMBER[3])
				{
					FUNC(GO,2);           FUNC(XUN,0);
					FUNC(TURN,90);        FUNC(XUN,0);
					if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
					if(FUNC(PUT,0)) RLED=0,printfloat(1);
					FUNC(TURN,180);				FUNC(XUN,0);
					FUNC(GO,2);						FUNC(XUN,0);
					FUNC(TURN,-90);				FUNC(XUN,0);
					if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
					FUNC(TURN,180);				FUNC(XUN,0);	
				}
				else
				{
						FUNC(GO,1);           FUNC(XUN,0); //第3级开始
						FUNC(GO,5);           FUNC(XUN,0);
						FUNC(NUM2,5);
						if(TARGET_NUM==NUMBER[4])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);       FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,90);				FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
					else if(TARGET_NUM==NUMBER[5])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,90);        FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,-90);				FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
					else
					{
					  FUNC(GO,1);           FUNC(XUN,0); //第4级开始
						FUNC(GO,5);           FUNC(XUN,0);
						FUNC(NUM2,7);
						if(TARGET_NUM==NUMBER[6])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,-90);       FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,90);				FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
					else if(TARGET_NUM==NUMBER[7])
					{
						FUNC(GO,2);           FUNC(XUN,0);
						FUNC(TURN,90);        FUNC(XUN,0);
						if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;           FUNC(XUN,0); 
						if(FUNC(PUT,0)) RLED=0,printfloat(1);
						FUNC(TURN,180);				FUNC(XUN,0);
						FUNC(GO,2);						FUNC(XUN,0);
						FUNC(TURN,-90);				FUNC(XUN,0);
						if(FUNC(GO,3)) GLED=1,printfloat(1); FUNC(XUN,0);
						FUNC(TURN,180);				FUNC(XUN,0);	
					}
						
						
					}
				}
		}
	
}
