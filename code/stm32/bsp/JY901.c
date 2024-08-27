#include "JY901.h"

void JY901_Clear(struct JY901_Uart *j)
{
	j->res=0; //接收数据
	for(int i=0;i<100;i++)
	{
		j->JY901_Data[i]=0; 
	}
	j->RxLine=0;
	j->Yew=0;
	j->Base_Flag=0;
	j->Base_Yew=0;
}

void Cal_Base_Angle(struct JY901_Uart *j)
{
	static uint16_t cnt=0;
	static uint32_t sum=0;
	
	if(cnt<200)
	{
		sum+=j->Yew;
		cnt++;
	}else{
		j->Base_Yew=sum/200;
		j->Base_Flag=1;
	}
}
