#ifndef __menu_Ui_H
#define __menu_Ui_H
#include <STC32G.H>
#include "lcd_init.h"
#include "lcd.h"
#include "system.h"

typedef struct{
	float Voltage_Value;
	float Current_Value;
	float Power_Value;
	float D_LEFT_Voltage_Value;
	float D_RIGHT_Voltage_Value;	
	
}ADC_Get_Value;
extern ADC_Get_Value ADC_Get;
typedef struct{
	float W_Max;
	float V_Max;
	float C_Max;
	float W_Min;
	float V_Min;
	float C_Min;	
}ADC_Power;

extern ADC_Power Range;

typedef struct{
	unsigned int humi;
	unsigned int temp;
	
}AHT;
extern AHT AHT10;

typedef struct{
	float ALL_Voltage_Value;
	float ALL_Current_Value;
}ALL_Value;
extern ALL_Value Line;

typedef struct{
	float protect_Current;
	float protect_Temp;
}Current_Temp_protect;
extern Current_Temp_protect C_T_P;

typedef struct{
	u8 Current_Range_Flag_one;
	u8 Current_Range_Flag_tow;
  u8 Current_Range_Flag_three;
  u8 Current_Range_Flag_four;
  u8 Current_Range_Flag_five;	
  u8 Current_Range_Flag_six;
  u8 Current_Range_Flag_seven;
  u8 Current_Range_Flag_eight;
	u8 Current_Range_Flag_nine;
  u8 Current_Range_Flag_ten;	
}Current_Range_Flag;
extern Current_Range_Flag C_Range;

extern float C_Max;
extern float V_Max;
extern float W_Max;

extern float ALL_temp;
extern u8 FLAGS;

extern u8 ADC_GET_V_X;
extern u8 ADC_GET_V_Y;

extern u8 Voltage_range_Flag;
extern u8 Voltage_range_Flag_Tow;
extern u8 Voltage_range_Flag_Three;
void menu_Ui_main(void);
u8 menu_Ui_Choose_Menu(u8 Menu_FLAG);
u8 menu_Ui_PD_QC_Menu(u8 Menu_FLAG);
void menu_Ui_Voltage_current_Line_Menu(void);

void menu_Ui_Current_Temp_protect(void);

void menu_Ui_PD_Voltage_Current(void);
void menu_Ui_QC_Voltage_Current(void);
#endif