#include "mission.h"
#include "syslib.h"

int STEP;
int target_step=-1;

int END(void)	//���������λ����
{
	target_step++;//Ŀ�������ż�1
	if(target_step==STEP)//���Ŀ����̺ŵ��ڱ����̺�
	{
		GLED=1;
		target_step=-1;//Ŀ����̺Ÿ�λ
		STEP=0;//�����̺Ÿ�λ
		RESET_ALL();	//��λPID������
		TARGET_NUM=0;	//����Ŀ������
		u1[0]=0;
		memset(NUMBER,0,sizeof(NUMBER));//����ʶ�����ֻ�������
		return 1;//���ؽ�����ɱ�־λ
	}
	return 0;
}


void host(void) //��������
{	
  if(FUNC(TARGET,0)) GLED=0,WIFI_FLAG=1; //���Ŀ������
  FUNC(PUT,1);  //���ҩ��
  
	if(TARGET_NUM==1)
	{
		FUNC(GO,2);             FUNC(XUN,0); //ǰ����LEN2==0
		FUNC(TURN,-90);         FUNC(XUN,0); //��ת90��
		if(FUNC(GO,3)) RLED=1,WIFI_FLAG=2;  FUNC(XUN,0); //ǰ����LEN1==0
		if(FUNC(PUT,0)) RLED=0;              //���ҩ�ﱻȡ��
		FUNC(TURN,180);					FUNC(XUN,0); //��ת180��
		FUNC(GO,2);							FUNC(XUN,0); //ǰ����LEN2=0
		FUNC(TURN,90);					FUNC(XUN,0); 
		if(FUNC(GO,3)) GLED=1; FUNC(XUN,0);  //ǰ����LEN1==0
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
	
	else //�ж˿�ʼ
	{	
		FUNC(GO,4); FUNC(XUN,0);  //ǰ�����ж�LEN1��
		FUNC(GO,5); FUNC(XUN,0);  //���˶�������
		FUNC(NUM2,1);             //ʶ��2������
		
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
		else//Զ�˿�ʼ
		{
			FUNC(GO,6);  //�Թ�1����LEN2ͣ��
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
			else //Զ���ұ߿�ʼ
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

void slave(void) //�ӻ�����
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
		else//Զ�˿�ʼ
		{
			FUNC(GO,6);  //�Թ�1����LEN2ͣ��
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
			else //Զ���ұ߿�ʼ
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
	target_step=-1;//���̵��ȱ�־λ��λ

};

void map2(void)
{
			if(FUNC(TARGET,0)) GLED=0; //���Ŀ������
			FUNC(PUT,1);  //���ҩ��
			FUNC(GO,1);           FUNC(XUN,0); //��1����ʼ
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
					FUNC(GO,1);           FUNC(XUN,0); //��2����ʼ
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
						FUNC(GO,1);           FUNC(XUN,0); //��3����ʼ
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
					  FUNC(GO,1);           FUNC(XUN,0); //��4����ʼ
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
