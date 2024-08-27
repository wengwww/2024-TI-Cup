#ifndef __MY_UART_H
#define __MY_UART_H

#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>

#define SCREEN_UART huart3
#define CAMERA_UART huart2
#define VOFA_UART huart1
#define BLUETOOTH_UART huart2
#define JY901_UART huart3

#define SCREEN_RXLINE_MAX 50
#define CAMERA_RXLINE_MAX 200
#define VOFA_RXLINE_MAX 200
#define BLUETOOTH_RXLINE_MAX 100
#define JY901_RXLINE_MAX 11

//串口屏
struct Screen 
{
	uint8_t res; //接收数据
	uint8_t Screen_Data[SCREEN_RXLINE_MAX]; 
	uint8_t RxLine;

	uint8_t question; //选题
};

//树莓派
struct Camera
{
	uint8_t res; //接收数据
	uint8_t Camera_Data[CAMERA_RXLINE_MAX]; 
	uint8_t RxLine;
};

//vofa调参
struct Vofa_Test
{
	uint8_t res; //接收数据
	uint8_t Vofa_Data[VOFA_RXLINE_MAX]; 
	uint8_t RxLine;
};

//蓝牙模块
struct Bluetooth
{
	uint8_t res; //接收数据
	uint8_t Bluetooth_Data[BLUETOOTH_RXLINE_MAX]; 
	uint8_t RxLine;
};

struct JY901_Uart
{
	uint8_t res;
	uint8_t JY901_Data[JY901_RXLINE_MAX]; 
	uint8_t RxLine;
	
	float Yaw;
	float Base_Yaw;
	float Base_Flag;
};

void Screen_Clear(struct Screen *s);
void Camera_Clear(struct Camera *c);
void Vofa_Clear(struct Vofa_Test *v);
void Bluetooth_Clear(struct Bluetooth *b);
void JY901_Clear(struct JY901_Uart *j);

void JY901_DataHandle(struct JY901_Uart *j); //只获取偏航角Yaw

#endif
