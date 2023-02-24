#ifndef __ADC_H
#define __ADC_H
#include "system.h"
#include <STC32G.H>
#include "uart1.h"

extern float ADC_Sun_Value;
void ADC_Init(void);

float ADC_Voltage_Read_Value(void);
float ADC_Voltage_Read_Value_average(void);
float ADC_Voltage_Read_Value_Line(void);
float ADC_Read_current_Value(void);
float ADC_Read_current_Value_average(void);
float ADC_Read_D_LEFT_Value(void);
float ADC_D_LEFT_Read_Value_average(void);
float ADC_Read_D_RIGHT_Value(void);
float ADC_D_RIGHT_Read_Value_average(void);
#endif