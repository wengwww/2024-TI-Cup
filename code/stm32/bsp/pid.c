#include "pid.h"

void initPID(float kp,float ki,float kd,float high,float low,struct pidstruct *e)//初始化pid
{
	e->kp=kp;
	e->ki=ki;
	e->kd=kd;
	e->p=0;
	e->i=0;
	e->d=0;
	e->lastde=0;
	e->thisde=0;
	e->outhigh=high;
	e->outlow=low;
	e->i_flag=1;
}

//带积分分离的pid
float PID(struct pidstruct *e,float target,float err)//返回pid结果
{
	float out;
	e->thisde=err;
	e->p=e->kp*e->thisde;
	if(e->i_flag) e->i=e->i+e->thisde;//修改了学长的PID函数
	e->d=e->kd*(e->thisde-e->lastde);
	e->lastde=e->thisde;

	//这里要防下一刹不住车
	if(target==0)
	{
		e->i=0;
	}

	out=e->p+e->ki*e->i+e->d;
	if(out>e->outhigh)	out=e->outhigh;
	if(out<e->outlow)	out=e->outlow;
	return out;
}


