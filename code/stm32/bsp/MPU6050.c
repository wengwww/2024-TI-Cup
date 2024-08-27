#include "MyI2C.h"
#include "MPU6050.h"

#define MPU6050_ADDRESS		0xD0  //写

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();//发送起始信号
	MyI2C_SendByte(MPU6050_ADDRESS);//发送mpu6050设备号及读写位（写）
	MyI2C_ReceiveAck();//等待从机响应
	MyI2C_SendByte(RegAddress);//发送要写入数据的寄存器的地址
	MyI2C_ReceiveAck();//等待从机响应
	MyI2C_SendByte(Data);//发送数据
	MyI2C_ReceiveAck();//等待从机响应
	MyI2C_Stop();//发送停止信号
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();//发送起始信号
	MyI2C_SendByte(MPU6050_ADDRESS);//发送mpu6050设备号及读写位（写）
	MyI2C_ReceiveAck();//等待从机响应
	MyI2C_SendByte(RegAddress);//发送要写入数据的寄存器的地址，此时mpu6050内部寄存器指针就会指向这个地址，下面再进行发送起始信号，见下方
	                           //并且发送mpu6050设备号及读写位（读）
	MyI2C_ReceiveAck();//等待从机响应
	MyI2C_Start();//二次起始，为读数据做准备
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);//发送mpu6050设备号及读写位（读）
	MyI2C_ReceiveAck();//等待从机响应
	Data = MyI2C_ReceiveByte();//读取八位数据
	MyI2C_SendAck(1);//向从机发送不想再读数据的响应
	MyI2C_Stop();//发送停止信号
	
	return Data;
}

void MPU6050_Init(void)
{
	//MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
//
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)//这就是根据MPU6050手册进行读取寄存器值的操作
{
	uint8_t DataH, DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}

