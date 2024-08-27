#ifndef __CAR_H
#define __CAR_H

#include "main.h"
#include "tim.h"

#define CAR_TIM htim4
#define LEFT_FORWARD_CHANNEL TIM_CHANNEL_1
#define LEFT_BACKWARD_CHANNEL TIM_CHANNEL_2
#define RIGHT_FORWARD_CHANNEL TIM_CHANNEL_4
#define RIGHT_BACKWARD_CHANNEL TIM_CHANNEL_3

#define CAR_PWM_MAX 1000

#define CAR_LEFT_TIM htim2
#define CAR_RIGHT_TIM htim3

#define LEFT_RELOADVALUE __HAL_TIM_GetAutoreload(&CAR_LEFT_TIM)    //获取自动装载值,本例中为65535
#define LEFT_COUNTERNUM __HAL_TIM_GetCounter(&CAR_LEFT_TIM)        //获取编码器定时器中的计数值
#define RIGHT_RELOADVALUE __HAL_TIM_GetAutoreload(&CAR_RIGHT_TIM)    
#define RIGHT_COUNTERNUM __HAL_TIM_GetCounter(&CAR_RIGHT_TIM)

#define PI 3.1415926
#define MOTOR_SPEED_RERATIO 20u    //电机减速比
#define PULSE_PRE_ROUND 13 //一圈多少个脉冲
#define RADIUS_OF_TYRE 0.024 //轮胎半径，单位米
#define PERIMETER_OF_TYRE (2 * PI * RADIUS_OF_TYRE) //轮胎周长，单位米
#define WIDTH_OF_CAR 0.124 //车宽，单位米

//小车结构体
struct CarGesture{
	
	float LeftDistance;
	float RightDistance;
	float Distance;	//位移=(L+R)/2
	float LastLeftDistance;
	float LastRightDistance;
	float LastDistance;	//上一次位移
	float TargetDistance;//目标位移

	int IsForward_Left;
	int IsForward_Right;
	
	//左右轮速度环
	float RightSpeed;
	float LeftSpeed;
	float LeftTargetV;
	float RightTargetV;
	float ErrorLV;
	float ErrorRV;
	
	float ErrorV;

	int LeftTotalcount;
	int RightTotalcount;

	float Speed_Filter_Left[20];
	float Speed_Filter_Right[20];
	
	float Angle;
	float LastAngle;
	float TargetAngle;
	float ErrorAng;
	
	float Speed;
	float LastSpeed;
	float TargetSpeed;
	float ErrorS;
	
	float mileage;
	float BiasCam;
	float BiasArea;
};

void Car_Clear(struct CarGesture* c);
void Set_TargetDistance(struct CarGesture *c,float TagDistance);
void Set_TargetSpeed(struct CarGesture *c,float VL,float VR);
void Set_TargetAng(struct CarGesture *c,float Ang);

void Cal_ErrorV(struct CarGesture *c);
void Cal_ErrorS(struct CarGesture *c);
void Cal_ErrorAng(struct CarGesture *c);

float Speed_Low_Filter(float new_Spe,float *speed_Record);
void Cal_SpeedAng(struct CarGesture *c);
void Set_PWM(struct CarGesture *c ,float LRate,float RRate);

#endif
