#include "LED.h"

void LED_Init(void)
{
	HAL_GPIO_WritePin(LED_TEST_GPIO_Port,LED_TEST_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port,LED_YELLOW_Pin,GPIO_PIN_RESET);
}


void LED_TEST_OnOff(uint8_t state)
{
	if(state==1)
	{
		HAL_GPIO_WritePin(LED_TEST_GPIO_Port,LED_TEST_Pin,GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_TEST_GPIO_Port,LED_TEST_Pin,GPIO_PIN_SET);
	}
}

void LED_TEST_Sparkling()
{
	//100hz
	static int cnt=0;
	if(cnt<100)
	{
		cnt++;
	}
	if(cnt==100)
	{
		cnt=0;
		HAL_GPIO_TogglePin(LED_TEST_GPIO_Port,LED_TEST_Pin);
	}
}

void LED_RED_OnOff(uint8_t state)
{
	if(state==1)
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_RESET);
	}
}

void LED_GREEN_OnOff(uint8_t state)
{
	if(state==1)
	{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET);
	}
}

void LED_YELLOW_OnOff(uint8_t state)
{
	if(state==1)
	{
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port,LED_YELLOW_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port,LED_YELLOW_Pin,GPIO_PIN_RESET);
	}
}
