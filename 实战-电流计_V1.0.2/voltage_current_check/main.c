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
/*------------------------------USB��ţ���ʼ�-------------------------------
���ߣ�С��
���ܣ�������ѹ���ʼ��
      PD��QC��ƭ
			��ѹ����������ʾ
			���£����ر���
			�����¶�ʪ�ȼ��
ʱ�䣺2023/11/5-2023/2/21
�汾��1.1
*/
/*------------------------------����-------------------------------
���ߣ�С��
���ܣ����Ah��Wh����(ȥ������͵���鹦��)
ʱ�䣺2023/2/22
�汾��1.1.1
*/
/*------------------------------����-------------------------------
���ߣ�С��
���ܣ����C��PD�����ʱ�ر�NMOS�ܹرպ�˵�USBA��
      ȡ�����ع���ʱ�Զ��ָ������back����ȡ�����غ͹���
ʱ�䣺2023/2/23
�汾��1.1.2
*/
int main(void){

	GPIO_Init();
	P16 =0;
	Uart1_Init();

	LCD_Init();//LCD��ʼ��
  #if 1
	C_T_P.protect_Temp=60;
	C_T_P.protect_Current=4;
	ADC_Init();
		
	AHT10_State();
  Timer0_Init();
	Timer1_Init();
	Timer2_Init();
	
	PD_Bgegin(); //PD���
  PD_Power_Output();//PD���ʼ��
	CH224K_PD_Voltage(OUTPUT_5V); //PD���5V
	P16 =1;
	Delay_ms(100);
	LCD_Fill(0,0,240,135,WHITE);
	
	Progress_bar_Write(30, 55, 210, 75,GREEN,GRAY,BLACK,WHITE,10,100,DISABEL);//��������ʾ
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
