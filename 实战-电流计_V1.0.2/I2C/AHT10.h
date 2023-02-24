#ifndef __AHT10_H
#define __AHT10_H
#include "system.h"
#include <STC32G.H>
#include "uart1.h"
#include "I2C.h"

#define AHT_ADDRESS 0X70 //0X38
#define AHT_WRITE   0X70
#define AHT_READ    0X71 //0X39
u8 AHT10_State(void);
void AHT10_Write_Reset(void);
u8 AHT10_Read_Humi_Temp( unsigned int *HUMI,  unsigned int *TEMP);
#endif