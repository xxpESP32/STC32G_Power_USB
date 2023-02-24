#ifndef __Timer_H
#define __Timer_H
#include <STC32G.H>
#include "system.h"
#include "ADC.h"

extern u16 X_Voltage_Line;
extern u16 Y_Voltage_Line;

extern u16 X_Current_Line;
extern u16 Y_Current_Line;
extern u8 X_Line_Loop_FLAG;

extern u16 time;
extern u16 Change_Time;
extern unsigned long time_nember;

typedef struct{
	u16 H;
	u16 M;
	u16 S;	
}Time_Display;

extern Time_Display T_D;
extern float umA_Num_Sum;
extern float uW_Num_Sum;

void Timer0_Init(void);
extern u8 Dispaly_Ch_Flag;
void Timer1_Init(void);

void Timer2_Init(void);
#endif