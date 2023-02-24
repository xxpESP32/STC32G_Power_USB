#include <STC32G.H>
#include "ADC.h"
#include "UART1.h"
#include "I2C.h"
#include "AHT10.h"
#include "lcd_init.h"
#include "lcd.h"
#include "Key.h"
#include "Timer.h"
#include "menu.h"
#include "menu_Ui.h"
#include "String.h"
#include "CH224K.h"
#include "Pwm.h"
/*------------------------------USB夔牛功率计-------------------------------
作者：小夏
功能：电流电压功率检测
      PD，QC诱骗
			电压电流曲线显示
			过温，过载保护
			板上温度湿度检测
时间：2023/11/5-2023/2/21
版本：1.1
*/
/*------------------------------更新-------------------------------
作者：小夏
功能：添加Ah和Wh计算(去除电阻和电池组功能)
时间：2023/2/22
版本：1.1.1
*/
/*------------------------------更新-------------------------------
作者：小夏
功能：添加C口PD快充检测时关闭NMOS管关闭后端的USBA口
      取消过载过温时自动恢复，添加back按键取消过载和过温
时间：2023/2/23
版本：1.1.2
*/
int main(void){

	GPIO_Init();
	P16 =0;
	Uart1_Init();

	LCD_Init();//LCD初始化
  #if 1
	C_T_P.protect_Temp=60;
	C_T_P.protect_Current=4;
	ADC_Init();
		
	AHT10_State();
  Timer0_Init();
	Timer1_Init();
	Timer2_Init();
	
	PD_Bgegin(); //PD检测
  PD_Power_Output();//PD功率检测
	CH224K_PD_Voltage(OUTPUT_5V); //PD输出5V
	P16 =1;
	Delay_ms(100);
	LCD_Fill(0,0,240,135,WHITE);
	
	Progress_bar_Write(30, 55, 210, 75,GREEN,GRAY,BLACK,WHITE,10,100,DISABEL);//进度条显示
	LCD_Fill(0,0,240,135,BLACK);
	menu_Ui_main_Rect_set_steup();
  Range.C_Max=ADC_Read_current_Value_average()*1.794;
	Range.V_Max=ADC_Voltage_Read_Value_average();
	Range.W_Max=Range.C_Max*Range.V_Max;
	Range.C_Min=Range.C_Max; Range.V_Min=Range.V_Max;Range.W_Min=Range.W_Max;

  #endif
	
	while(1){

		Key_EVENT();

	}
}
