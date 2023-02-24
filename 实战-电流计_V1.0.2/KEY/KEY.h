#ifndef __KEY_H
#define __KEY_H
#include "system.h"
#include <STC32G.H>
#define KEY_LEFT_Read P21
#define KEY_ENTER_Read P22
#define KEY_BACK_Read P23
#define RESET  0
#define SET    1
extern u8 Clear_FLAG;
void KEY_Init(void);
void menu_Ui_main_Rect_set_steup(void);
void menu_Ui_main_Line(u16 color);
void Key_EVENT(void);
void Reset_Display_X_Line(void);
void Display_main_Line(void);
void Display_main_Line_Voltage(void);
extern u8 Time_Change_FLAG;
void Change_Timer_Time(void);
void menu_Ui_main_Line_Wen(u16 color);
extern u8 Begin_Stop_Flag;
extern u8 Begin_Stop_Ri_Flag;
void Diaplay_Begin_Stop(u8 indexs);
void Current_Temp_Ui(void);
void Current_Temp_add(void);
void Current_Temp_Set_succeed(void);
#endif