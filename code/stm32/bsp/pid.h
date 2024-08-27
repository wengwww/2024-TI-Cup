#ifndef __PID_H
#define __PID_H

#include "stm32f1xx_hal.h"
#include "main.h"

struct pidstruct//PID结构
{
	float kp,ki,kd;
	float  p, i, d;
	float thisde,lastde;
	float outhigh, outlow;
	
	int i_flag;
};

void initPID(float kp,float ki,float kd,float high,float low,struct pidstruct *e);
float PID(struct pidstruct *e,float target,float err);

#endif
