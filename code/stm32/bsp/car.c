#include "car.h"

void Car_Clear(struct CarGesture* c)
{
	c->LeftDistance=0;
	c->RightDistance=0;
	c->Distance=0;
	
	c->LastDistance=0;
	c->LastLeftDistance=0;
	c->LastRightDistance=0;
	c->TargetDistance =0;
	
	c->IsForward_Left=0;
	c->IsForward_Right=0;

	int i=0;
	for(i=0;i<20;i++)
	{
		c->Speed_Filter_Left[i]=0;
		c->Speed_Filter_Right[i]=0;
	}
	
	c->RightSpeed=0;
	c->LeftSpeed=0;
	c->RightTargetV=0;
	c->LeftTargetV =0;	
	c->ErrorLV=0;
	c->ErrorRV =0;
	
	c->ErrorV=0;

	c->LeftTotalcount=0;
	c->RightTotalcount=0;

	c->Speed=0;
	c->LastSpeed=0;
	c->TargetSpeed=0;
	c->ErrorS=0;

	c->LastAngle =0;
	c->Angle =0;
	c->ErrorAng =0;
	c->TargetAngle =0;
	
	c->mileage =0;
	c->BiasCam =0;
	c->BiasArea=0;
}

//设置目标距离
void Set_TargetDistance(struct CarGesture *c,float TagDistance)
{
	c->TargetDistance=TagDistance;
}
//设置目标速度
void Set_TargetSpeed(struct CarGesture *c,float VL,float VR)
{	
	c->LeftTargetV =VL;
	c->RightTargetV =VR;
	c->TargetSpeed =(VL+VR)/2;
}
//设置目标角度
void Set_TargetAng(struct CarGesture *c,float Ang)
{	
	c->TargetAngle =Ang;
}
//计算速度误差
void Cal_ErrorV(struct CarGesture *c)
{
	c->ErrorLV =c->LeftTargetV -c->LeftSpeed ;
	c->ErrorRV =c->RightTargetV -c->RightSpeed ;
}
//计算位移误差
void Cal_ErrorS(struct CarGesture *c)
{
	c->ErrorS=c->TargetDistance-c->Distance;
}
void Cal_ErrorAng(struct CarGesture *c)
{
	c->ErrorAng=c->TargetAngle-c->Angle;
}
//速度滤波
float Speed_Low_Filter(float new_Spe,float *speed_Record)
{
    float sum = 0.0f;
	static uint8_t cnt=0;

	for(uint8_t i=20-1;i>0;i--)
	{
		speed_Record[i] = speed_Record[i-1];
		if(speed_Record[i]!=0)
			cnt++;
		sum += speed_Record[i-1];
	}
	speed_Record[0] = new_Spe;
	if(new_Spe!=0) cnt++;
	sum += new_Spe;
	return sum/20;
}
//带�?�度滤波的计算�?�度角度
void Cal_SpeedAng(struct CarGesture *c)
{
	//速度滤波
	c->LeftSpeed=Speed_Low_Filter((c->LeftDistance-c->LastLeftDistance),c->Speed_Filter_Left);
	c->RightSpeed=Speed_Low_Filter((c->RightDistance-c->LastRightDistance),c->Speed_Filter_Right);

	//左右轮位移
	c->LastLeftDistance=c->LeftDistance;
	c->LastRightDistance=c->RightDistance;

	c->LastSpeed =c->Speed;
	c->Speed =(c->LeftSpeed+c->RightSpeed)/2.0f;
	//10ms的计算周期，cm的量纲，正好合成m/s	

	//转弯合成角度
	//c->Angle =c->Angle+(c->LeftSpeed -c->RightSpeed)*0.01f *360/(PI*WIDTH_OF_CAR)/2; 
}

void Set_PWM(struct CarGesture *c ,float LRate,float RRate) 
{	
	if(LRate>=0){
		__HAL_TIM_SET_COMPARE(&CAR_TIM,LEFT_FORWARD_CHANNEL,(uint16_t)(CAR_PWM_MAX-LRate*CAR_PWM_MAX));
		__HAL_TIM_SET_COMPARE(&CAR_TIM,LEFT_BACKWARD_CHANNEL,CAR_PWM_MAX);
		c->IsForward_Left=1;		
	}else {
		__HAL_TIM_SET_COMPARE(&CAR_TIM,LEFT_FORWARD_CHANNEL,CAR_PWM_MAX);
		__HAL_TIM_SET_COMPARE(&CAR_TIM,LEFT_BACKWARD_CHANNEL,(uint16_t)(CAR_PWM_MAX+LRate*CAR_PWM_MAX));
		c->IsForward_Left=0;		
	}
	if(RRate>=0){
		__HAL_TIM_SET_COMPARE(&CAR_TIM,RIGHT_FORWARD_CHANNEL,(uint16_t)(CAR_PWM_MAX-RRate*CAR_PWM_MAX));
		__HAL_TIM_SET_COMPARE(&CAR_TIM,RIGHT_BACKWARD_CHANNEL,CAR_PWM_MAX);
		c->IsForward_Right=1;	
	}else{
		__HAL_TIM_SET_COMPARE(&CAR_TIM,RIGHT_FORWARD_CHANNEL,CAR_PWM_MAX);
		__HAL_TIM_SET_COMPARE(&CAR_TIM,RIGHT_BACKWARD_CHANNEL,(uint16_t)(CAR_PWM_MAX+RRate*CAR_PWM_MAX));
		c->IsForward_Right=0;
	}
}

