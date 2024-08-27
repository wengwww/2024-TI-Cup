#include "my_uart.h"

void Screen_Clear(struct Screen *s)
{
	s->res=0; //接收数据
	for(int i=0;i<SCREEN_RXLINE_MAX;i++)
	{
		s->Screen_Data[i]=0; 
	}
	s->RxLine=0;
	s->question='0';
}

void Camera_Clear(struct Camera *c)
{
	c->res=0; //接收数据
	for(int i=0;i<CAMERA_RXLINE_MAX;i++)
	{
		c->Camera_Data[i]=0; 
	}
	c->RxLine=0;
}

void Vofa_Clear(struct Vofa_Test *v)
{
	v->res=0; //接收数据
	for(int i=0;i<VOFA_RXLINE_MAX;i++)
	{
		v->Vofa_Data[i]=0; 
	}
	v->RxLine=0;
}

void Bluetooth_Clear(struct Bluetooth *b)
{
	b->res=0; //接收数据
	for(int i=0;i<BLUETOOTH_RXLINE_MAX;i++)
	{
		b->Bluetooth_Data[i]=0; 
	}
	b->RxLine=0;
}
void JY901_Clear(struct JY901_Uart *j)
{
	j->res=0; //接收数据
	for(int i=0;i<JY901_RXLINE_MAX;i++)
	{
		j->JY901_Data[i]=0; 
	}
	j->RxLine=0;
	j->Yaw=0;
	j->Base_Flag=0;
	j->Base_Yaw=0;
}

/****串口解析函数****/

//JY901获取偏航角
void JY901_DataHandle(struct JY901_Uart *j)
{
	if(j->JY901_Data[0]==0x55 && j->JY901_Data[1]==0x53)
	{
		j->Yaw=((int16_t)((j->JY901_Data[7]<<8)|j->JY901_Data[6]))/32768.0*180.0;
	}
}

