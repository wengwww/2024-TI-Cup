#include "BUZZ.h"

void BUZZ_Init(void)
{
	HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_SET);
}

void BUZZ_OnOff(uint8_t state)
{
	if(state==1)
	{
		HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(BUZZ_GPIO_Port,BUZZ_Pin,GPIO_PIN_SET);
	}
}

