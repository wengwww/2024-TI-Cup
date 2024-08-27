#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "main.h"

void LED_Init(void);
void LED_TEST_OnOff(uint8_t state);
void LED_TEST_Sparkling(void);

void LED_RED_OnOff(uint8_t state);
void LED_GREEN_OnOff(uint8_t state);
void LED_YELLOW_OnOff(uint8_t state);

#endif
