#ifndef __I2C_H
#define __I2C_H

#include <STC32G.H>
#include "System.h"

#define I2C_GPIO_1 1  //SDA -> P14 SCL->P15
#define I2C_GPIO_2 2	//SDA -> P24 SCL->P25
#define I2C_GPIO_3 3	//SDA -> P33 SCL->P32

void I2C_Init(u8 Mode);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send_Byte(u8 dat);
void I2C_Wait_ACK(void);
u8 I2C_Read_Byte(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Delay(void);
#endif