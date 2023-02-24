/*
*ע�⣺ʹ��keil��Ҫ����ΪGB2312
*==============================�༶�˵�Դ�ļ�=======================
*-------------------------------------------------------------------
*�ļ��޸���ʷ
*<ʱ��>    | <�汾>  | <����>  | <����>  
*2023.2.24 | V1.0.2   | С��    | �༶�˵�UI��ʾ��PD��ƭ����,������ʾ����ȣ�
*-------------------------------------------------------------------
*/

#include "menu_Ui.h"
#include "String.h"
#include "I2C.h"
#include "AHT10.h"
#include "ADC.h"
//#include "Pic.h"
#include "menu.h"
#include "KEY.h"
#include "TIMER.h"
ADC_Get_Value ADC_Get;
float ADC_Voltage;
float ALL_temp=0;
AHT AHT10;
u8 humi_char[12];
u8 temp_char[12];
//������
u8 Power;
u8 Power_String[12];
u8 FLAGS;

float ADC_Max_Min;

u8 ADC_GET_V_X=10;
u8 ADC_GET_V_Y=100;
u16 CH_Y;
u8 Voltage_range_Flag;
u8 Voltage_range_Flag_Tow;
u8 Voltage_range_Flag_Three;

ALL_Value Line;
Current_Range_Flag C_Range;
u8 Voltage_Ripple_Nember=13;

ADC_Power Range;

Current_Temp_protect C_T_P;
u16 Temp_ALL_Value;
u8 Voltage_Level_Flag;
u8 fast_charge_Flag;

/*-------------------------------------------------------------
*���ܣ�һ�����������ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_main(void){

  ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	//��ʾ��ѹ 36*36
	LCD_ShowFloatNum1(4,19,  ADC_Get.Voltage_Value,5,YELLOW,BLACK,32);
	LCD_ShowString(104,19,"V",YELLOW,BLACK,32,0);
  
	//��ʾ���� 36*36	
	ADC_Get.Current_Value=ADC_Read_current_Value_average();//0.0399
	LCD_ShowFloatNum1(4,50,	ADC_Get.Current_Value,5,BLUE,BLACK,32);
	LCD_ShowString(104,50,"A",BLUE,BLACK,32,0);	
	//��ʾ���� 36*36	
	LCD_ShowFloatNum1(4,82,	ADC_Get.Current_Value*ADC_Get.Voltage_Value,5,RED_NOW,BLACK,32);
	LCD_ShowString(104,82,"W",RED_NOW ,BLACK,32,0);  
	//��ʾ��ʪ��	
	
  AHT10_Read_Humi_Temp(&AHT10.humi,&AHT10.temp);
	ALL_temp=((AHT10.temp/100)*10)+(AHT10.temp%100/10);
  sprintf(humi_char,"%d%d.%d%%",AHT10.humi/100,AHT10.humi%100/10,AHT10.humi%100%10);
	sprintf(temp_char,"%d%d.%dC",AHT10.temp/100,AHT10.temp%100/10,AHT10.temp%100%10);
	LCD_ShowString(162,0,temp_char,RED,BLACK,12,0);
	LCD_Fill(192,0,204,12,BLACK);
	LCD_ShowString(209,0,humi_char,GREEN,BLACK,12,0);		
	//��ʾ����
//	LCD_ShowFloatNum(150,21,	ADC_Get.Voltage_Value/ADC_Get.Current_Value,6,PINK_RED,BLACK,16);
//	LCD_ShowString(225-18,21,"R",PINK_RED,BLACK,16,0); 	
//	//��ʾ������
//	LCD_ShowChinese16x16(151,40,"��",WHITE,BLACK,16,0);
//	LCD_ShowChinese16x16(151+16,40,"��",WHITE,BLACK,16,0);
//	if(ADC_Get.Voltage_Value>=0 && ADC_Get.Voltage_Value<=6.0) Power=1;	
//	if(ADC_Get.Voltage_Value>=6.0 && ADC_Get.Voltage_Value<=10.0) Power=2;
//	if(ADC_Get.Voltage_Value>=10.0 && ADC_Get.Voltage_Value<=13.0) Power=3;
//	if(ADC_Get.Voltage_Value>=13.0 && ADC_Get.Voltage_Value<=17) Power=4;
//	if(ADC_Get.Voltage_Value>=17.0 && ADC_Get.Voltage_Value<=21) Power=5;	
//	sprintf(Power_String,"%d/5",Power);
//	LCD_ShowString(151+34,40,Power_String,WHITE,BLACK,16,0);	
  //��ʾWh
	//��ʾʱ��
	LCD_ShowIntNum(151+8,18,T_D.H,2,WHITE,BLACK,12);
	LCD_ShowString(151+12+8,18,":",WHITE,BLACK,12,0);
	LCD_ShowIntNum(151+12+8+8,18,T_D.M,2,WHITE,BLACK,12);
	LCD_ShowString(151+20+12+8,18,":",WHITE,BLACK,12,0);	
	LCD_ShowIntNum(151+20+12+8+8,18,T_D.S,2,WHITE,BLACK,12);
  //��ʾmah

	LCD_ShowFloatNum5(151+8,18+12,umA_Num_Sum,6,BLUE,BLACK,12);
	LCD_ShowString(151+8+36+8,18+12,"Ah",BLUE,BLACK,12,0);
	LCD_ShowFloatNum5(151+8,18+24,uW_Num_Sum,6,YELLOW,BLACK,12);
	LCD_ShowString(151+8+36+8,18+24,"Wh",YELLOW,BLACK,12,0);	
	//��ʾ����ѹ������������
	LCD_ShowString(150,59,"MAX",RED,BLACK,12,0);
	LCD_ShowString(198,59,"MIN",GREEN,BLACK,12,0);
	
	if(Range.V_Max<ADC_Get.Voltage_Value) Range.V_Max=ADC_Get.Voltage_Value;	
	LCD_ShowFloatNum1(138,71,	Range.V_Max,5,YELLOW,BLACK,12);//��ѹ���ֵ
	LCD_ShowString(174,71,"V",YELLOW,BLACK,12,0);

	if(Range.C_Max<ADC_Get.Current_Value) Range.C_Max=ADC_Get.Current_Value;
	LCD_ShowFloatNum1(138,82,	Range.C_Max,5,BLUE,BLACK,12);//�������ֵ	
	LCD_ShowString(174,82,"A",BLUE,BLACK,12,0);
	
	ADC_Get.Power_Value=ADC_Get.Current_Value*ADC_Get.Voltage_Value;
  if(Range.W_Max<ADC_Get.Power_Value) Range.W_Max=ADC_Get.Power_Value;	
	LCD_ShowFloatNum1(138,94,Range.W_Max,5,RED_NOW,BLACK,12);//�������ֵ	
	LCD_ShowString(174,94,"W",RED_NOW,BLACK,12,0);	
	//��ʾ��С��ѹ������������
		if(Range.V_Min>ADC_Get.Voltage_Value) Range.V_Min=ADC_Get.Voltage_Value;
	LCD_ShowFloatNum1(188,71,	Range.V_Min,5,YELLOW,BLACK,12);//��ѹ��Сֵ
	LCD_ShowString(188+36,71,"V",YELLOW,BLACK,12,0);
	
		if(Range.C_Min>ADC_Get.Current_Value) Range.C_Min=ADC_Get.Current_Value;
	LCD_ShowFloatNum1(188,82,	Range.C_Min,5,BLUE,BLACK,12);//������Сֵ	
	LCD_ShowString(188+36,82,"A",BLUE,BLACK,12,0);

		if(Range.W_Min>ADC_Get.Power_Value) Range.W_Min=ADC_Get.Power_Value;	
	LCD_ShowFloatNum1(188,94,	Range.W_Min,5,RED_NOW,BLACK,12);//������Сֵ	
	LCD_ShowString(188+36,94,"W",RED_NOW,BLACK,12,0);	
	//��ʾNOMS����״̬
	LCD_ShowString(5,120,"NMOS:",BLUE,BLACK,16,0);
	if(P16==1){
		LCD_ShowChinese12x12(48,123,"��",WHITE,BLACK,12,0);
	}else{
		LCD_ShowChinese12x12(48,123,"��",WHITE,BLACK,12,0);		
	}
	if(Dispaly_Ch_Flag==0){			
		LCD_ShowChinese12x12(68,123,"һ",GREEN,BLACK,12,0);
		LCD_ShowChinese12x12(68+12,123,"��",GREEN,BLACK,12,0);	
		LCD_ShowChinese12x12(68+24,123,"��",GREEN,BLACK,12,0);
		LCD_ShowChinese12x12(68+36,123,"��",GREEN,BLACK,12,0);  
	}else if(Dispaly_Ch_Flag==1){			
		LCD_ShowChinese12x12(68,123,"��",RED,BLACK,12,0);
		LCD_ShowChinese12x12(68+12,123,"��",RED,BLACK,12,0);	
		LCD_ShowChinese12x12(68+24,123,"��",RED,BLACK,12,0);
		LCD_ShowChinese12x12(68+36,123,"��",RED,BLACK,12,0);  
	}else if(Dispaly_Ch_Flag==2){			
		LCD_ShowChinese12x12(68,123,"��",RED,BLACK,12,0);
		LCD_ShowChinese12x12(68+12,123,"��",RED,BLACK,12,0);	
		LCD_ShowChinese12x12(68+24,123,"��",RED,BLACK,12,0);
		LCD_ShowChinese12x12(68+36,123,"��",RED,BLACK,12,0);  
	}
  //��ʾD+,D-
	ADC_Get.D_LEFT_Voltage_Value=ADC_D_LEFT_Read_Value_average();
	LCD_ShowString(140,110,"D+:",YELLOW,BLACK,12,0);
  LCD_ShowFloatNum1(140+24,110,ADC_Get.D_LEFT_Voltage_Value,5,YELLOW,BLACK,12);
	LCD_ShowString(140+24+36,110,"V",YELLOW,BLACK,12,0);
	
	ADC_Get.D_RIGHT_Voltage_Value=ADC_D_RIGHT_Read_Value_average();
	LCD_ShowString(140,122,"D-:",GREEN,BLACK,12,0);
  LCD_ShowFloatNum1(140+24,122,ADC_Get.D_RIGHT_Voltage_Value,5,GREEN,BLACK,12);
	LCD_ShowString(140+24+36,122,"V",GREEN,BLACK,12,0);	
	//��ʾ�Ƿ񴥷����Э��
	LCD_ShowChinese12x12(4,0,"��",WHITE,BLACK,12,0);
	LCD_ShowChinese12x12(4+12,0,"��",WHITE,BLACK,12,0);	
	LCD_ShowChinese12x12(4+24,0,"��",WHITE,BLACK,12,0);
	LCD_ShowChinese12x12(4+36,0,"��",WHITE,BLACK,12,0);
	LCD_ShowChinese12x12(4+48,0,"��",WHITE,BLACK,12,0);
	LCD_ShowChinese12x12(4+60,0,"��",WHITE,BLACK,12,0);
	//----------------------------------���Э����---------------------------------------------
	if((ADC_Get.D_LEFT_Voltage_Value>0.4&&ADC_Get.D_LEFT_Voltage_Value<0.9)&&(ADC_Get.D_RIGHT_Voltage_Value>0&&ADC_Get.D_RIGHT_Voltage_Value<0.3)){
		fast_charge_Flag=1;
	  LCD_ShowString(80+12+10,0,"QC2  5V",GREEN,BLACK,12,0);		
	}else if((ADC_Get.D_LEFT_Voltage_Value>2.2&&ADC_Get.D_LEFT_Voltage_Value<3.3)&&(ADC_Get.D_RIGHT_Voltage_Value>0.5&&ADC_Get.D_RIGHT_Voltage_Value<0.9)){
		fast_charge_Flag=1;
	  LCD_ShowString(80+12+10,0,"QC2  9V",GREEN,BLACK,12,0);					
	}else if((ADC_Get.D_LEFT_Voltage_Value>0.4&&ADC_Get.D_LEFT_Voltage_Value<0.9)&&(ADC_Get.D_RIGHT_Voltage_Value>0.5&&ADC_Get.D_RIGHT_Voltage_Value<0.9)){
		fast_charge_Flag=1;
	  LCD_ShowString(80+12+10,0,"QC2 12V",GREEN,BLACK,12,0);		
	}else if((ADC_Get.D_LEFT_Voltage_Value>2.2&&ADC_Get.D_LEFT_Voltage_Value<3.3)&&(ADC_Get.D_RIGHT_Voltage_Value>2.2&&ADC_Get.D_RIGHT_Voltage_Value<3.3)){
		fast_charge_Flag=1;
	  LCD_ShowString(80+12+10,0,"QC2 20V",GREEN,BLACK,12,0);		
	}else if((ADC_Get.D_LEFT_Voltage_Value>0.4&&ADC_Get.D_LEFT_Voltage_Value<0.9)&&(ADC_Get.D_RIGHT_Voltage_Value>2.2&&ADC_Get.D_RIGHT_Voltage_Value<3.3)){
		fast_charge_Flag=1;
	  LCD_ShowString(80+12+10,0,"QC  3.0",GREEN,BLACK,12,0);					
	}
	
	else{
		fast_charge_Flag =0;
	  LCD_ShowString(80+12+10,0,"N  None",GREEN,BLACK,12,0);
	}

	
	if(ADC_Get.Voltage_Value>=6|fast_charge_Flag==1 ){
		LCD_ShowChinese12x12(4+76,0,"��",RED,BLACK,12,0);				
	}else{
		LCD_ShowChinese12x12(4+76,0,"��",WHITE,BLACK,12,0);		
	}
}
/*-------------------------------------------------------------
*���ܣ������˵���ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
u8 menu_Ui_Choose_Menu(u8 Menu_FLAG){

	if(Menu_FLAG ==0){
		//�����ƭ
		LCD_ShowChinese24x24(8,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+24,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+48,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72,8,"ƭ",YELLOW,GREEN,24,0);
		//���߹���
		LCD_ShowChinese24x24(8,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,40,"��",YELLOW,BLACK,24,0);		
		//�����Ʋ�
		LCD_ShowChinese24x24(8,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,72,"ѹ",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,72,"��",YELLOW,BLACK,24,0);	
		//�����¶ȱ���
		LCD_ShowChinese24x24(8,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+48,104,"��",YELLOW,BLACK,24,0);		
		return 1;
	}
	if(Menu_FLAG ==1){
		//�����ƭ
		LCD_ShowChinese24x24(8,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,8,"ƭ",YELLOW,BLACK,24,0);
		//���߹���
		LCD_ShowChinese24x24(8,40,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+24,40,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+48,40,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72,40,"��",YELLOW,GREEN,24,0);		
		//�����Ʋ�
		LCD_ShowChinese24x24(8,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,72,"ѹ",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,72,"��",YELLOW,BLACK,24,0);	
		//�����¶ȱ���
		LCD_ShowChinese24x24(8,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+48,104,"��",YELLOW,BLACK,24,0);	
		return 2;		
	}
	if(Menu_FLAG ==2){
		//�����ƭ
		LCD_ShowChinese24x24(8,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,8,"ƭ",YELLOW,BLACK,24,0);
		//���߹���
		LCD_ShowChinese24x24(8,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,40,"��",YELLOW,BLACK,24,0);		
		//�����Ʋ�
		LCD_ShowChinese24x24(8,72,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+24,72,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+48,72,"ѹ",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72,72,"��",YELLOW,GREEN,24,0);	
		//�����¶ȱ���
		LCD_ShowChinese24x24(8,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+24,104,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72+48,104,"��",YELLOW,BLACK,24,0);			
		return 3;
	}
	if(Menu_FLAG ==3){
		LCD_ShowChinese24x24(8,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,8,"ƭ",YELLOW,BLACK,24,0);
		//���߹���
		LCD_ShowChinese24x24(8,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,40,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,40,"��",YELLOW,BLACK,24,0);		
		//�����Ʋ�
		LCD_ShowChinese24x24(8,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+24,72,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+48,72,"ѹ",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(8+72,72,"��",YELLOW,BLACK,24,0);	
		//�����¶ȱ���
		LCD_ShowChinese24x24(8,104,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+24,104,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+48,104,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72,104,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72+24,104,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(8+72+48,104,"��",YELLOW,GREEN,24,0);			
		return 4;
	}
	return 0;
}
/*-------------------------------------------------------------
*���ܣ������˵���->��ƭ������ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
u8 menu_Ui_PD_QC_Menu(u8 Menu_FLAG){

		if(Menu_FLAG==0){
		//PD���Э��
		LCD_ShowString(6,8,"PD",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+24,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+48,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+72,8,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+72+24,8,"ƭ",YELLOW,GREEN,24,0);
    //QC���Э��
		LCD_ShowString(6,35,"QC",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+48,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,35,"ƭ",YELLOW,BLACK,24,0);
    //��ͨ5V����

		LCD_ShowChinese24x24(6,67,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,67,"ͨ",YELLOW,BLACK,24,0);
		LCD_ShowString(6+48,67,"5V",YELLOW,BLACK,24,0);		
		LCD_ShowChinese24x24(6+72,67,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,67,"��",YELLOW,BLACK,24,0);
   // return 1;		
	}
	if(Menu_FLAG==1){
		//PD���Э��
		LCD_ShowString(6,8,"PD",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+48,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,8,"ƭ",YELLOW,BLACK,24,0);
    //QC���Э��
		LCD_ShowString(6,35,"QC",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+24,35,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+48,35,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+72,35,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+72+24,35,"ƭ",YELLOW,GREEN,24,0);
    //��ͨ5V����

		LCD_ShowChinese24x24(6,67,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,67,"ͨ",YELLOW,BLACK,24,0);
		LCD_ShowString(6+48,67,"5V",YELLOW,BLACK,24,0);		
		LCD_ShowChinese24x24(6+72,67,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,67,"��",YELLOW,BLACK,24,0);
   // return 2;		
		}
		if(Menu_FLAG==2){
		//PD���Э��
		LCD_ShowString(6,8,"PD",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+48,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72,8,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,8,"ƭ",YELLOW,BLACK,24,0);
    //QC���Э��
		LCD_ShowString(6,35,"QC",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+24,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+48,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72,35,"��",YELLOW,BLACK,24,0);
		LCD_ShowChinese24x24(6+72+24,35,"ƭ",YELLOW,BLACK,24,0);
    //��ͨ5V����

		LCD_ShowChinese24x24(6,67,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+24,67,"ͨ",YELLOW,GREEN,24,0);
		LCD_ShowString(6+48,67,"5V",YELLOW,GREEN,24,0);		
		LCD_ShowChinese24x24(6+72,67,"��",YELLOW,GREEN,24,0);
		LCD_ShowChinese24x24(6+72+24,67,"��",YELLOW,GREEN,24,0);
    //return 3;		
	}
	//��ʾ��ʪ��	
	
  AHT10_Read_Humi_Temp(&AHT10.humi,&AHT10.temp);
	ALL_temp=((AHT10.temp/100)*10)+(AHT10.temp%100/10);
  sprintf(humi_char,"%d%d.%d%%",AHT10.humi/100,AHT10.humi%100/10,AHT10.humi%100%10);
	sprintf(temp_char,"%d%d.%dC",AHT10.temp/100,AHT10.temp%100/10,AHT10.temp%100%10);
	LCD_ShowString(20,96,temp_char,RED,BLACK,16,0);
	LCD_DrawRectangle(11, 114, 64, 115,WHITE);
	LCD_ShowString(20,118,humi_char,GREEN,BLACK,16,0);		
	//��ʾͼƬ
	//LCD_ShowPicture(143,15,94,82,gImage_KUI);
	//��ʾUSB��ţ>>
	LCD_ShowString(145,113,"USB",BLUE,BLACK,16,0);
	LCD_ShowChinese16x16(145+24,113,"��",YELLOW,BLACK,16,0);
	LCD_ShowChinese16x16(145+24+16,113,"ţ",YELLOW,BLACK,16,0);	
	LCD_ShowString(145+25+32,113,">>",RED_NOW,BLACK,16,0);
		return 0;
}
/*-------------------------------------------------------------
*���ܣ������˵���->������ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_Voltage_current_Line_Menu(void){
	//��ʾ��ѹ
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_Line();
	LCD_ShowFloatNum1(45,3,  ADC_Get.Voltage_Value,5,YELLOW,BLACK,12);
	LCD_ShowString(81,3,"V",YELLOW,BLACK,12,0);
  
	//��ʾ���� 
	ADC_Get.Current_Value=ADC_Read_current_Value_average();
	LCD_ShowFloatNum1(154,3,	ADC_Get.Current_Value,5,BLUE,BLACK,12);
	LCD_ShowString(190,3,"A",BLUE,BLACK,12,0);

  //��ʾ����
	LCD_ShowFloatNum1(78,119,ADC_Get.Voltage_Value*ADC_Get.Current_Value,5,RED_NOW,BLACK,12);
	LCD_ShowString(114,119,"W",RED_NOW,BLACK,12,0);	
//��ʾ����
  if(Time_Change_FLAG==0) LCD_ShowString(102,3,"T:60S",WHITE,BLACK,12,0);	
	else if(Time_Change_FLAG==1) LCD_ShowString(102,3,"T:30S",WHITE,BLACK,12,0);	
	else if(Time_Change_FLAG==2) LCD_ShowString(102,3,"T:10S",WHITE,BLACK,12,0);		
	else if(Time_Change_FLAG==3) LCD_ShowString(102,3,"T:1S",WHITE,BLACK,12,0);	
	else if(Time_Change_FLAG==4) LCD_ShowString(102-6,3,"T:500ms",WHITE,BLACK,12,0);
	else if(Time_Change_FLAG==5) LCD_ShowString(102-6,3,"T:200ms",WHITE,BLACK,12,0);
	else if(Time_Change_FLAG==6) LCD_ShowString(102-6,3,"T:100ms",WHITE,BLACK,12,0);	
	else if(Time_Change_FLAG==7) LCD_ShowString(102-6,3,"T:50ms",WHITE,BLACK,12,0);
	else if(Time_Change_FLAG==8) LCD_ShowString(102-6,3,"T:20ms",WHITE,BLACK,12,0);
	if(Begin_Stop_Flag ==0){
	//ˢ�����ߵĵ�������
	if(X_Line_Loop_FLAG==1){
				ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
				ADC_Get.Current_Value=ADC_Read_current_Value_average();
				if(X_Voltage_Line>=220){ //ˢ�¹̶��Ŀ��ͼ
							X_Voltage_Line=11;
							X_Current_Line=10;
							LCD_Fill(0,17,240,119,BLACK);
							menu_Ui_main_Line(RED);
							//��ʾ����ѹ�͵���
					    // Voltage_Level_Flag;


					if(C_Range.Current_Range_Flag_one== 1){					
						//��ʾ��С��ѹ����	
						LCD_ShowString(213-12,3,"0.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}
					if(C_Range.Current_Range_Flag_tow== 1){					
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"1A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}
					if(C_Range.Current_Range_Flag_three== 1){					
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}
					if(C_Range.Current_Range_Flag_four== 1){					
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}
				}
       	 if(ADC_Get.Voltage_Value<6){
									//Voltage_Level_Flag
								LCD_ShowString(9,3,"6V",YELLOW,BLACK,12,0);
						    LCD_ShowString(9,119,"0V",YELLOW,BLACK,12,0);
				
								Line.ALL_Voltage_Value=114-(((ADC_Get.Voltage_Value-3)/9)*240);
					     	//LCD_ShowIntNum(20,119,Line.ALL_Voltage_Value,4,YELLOW,BLACK,12); 
								LCD_DrawLine(X_Voltage_Line,Y_Voltage_Line,X_Voltage_Line+=1,Line.ALL_Voltage_Value,YELLOW);
								Y_Voltage_Line=Line.ALL_Voltage_Value;
					      
				 }
				 if(ADC_Get.Voltage_Value<=10&&ADC_Get.Voltage_Value>6){
					LCD_ShowString(9,3,"10V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"6V",YELLOW,BLACK,12,0);
					Line.ALL_Voltage_Value=114-(((ADC_Get.Voltage_Value-6)/12)*240);
					LCD_DrawLine(X_Voltage_Line,Y_Voltage_Line,X_Voltage_Line+=1,Line.ALL_Voltage_Value,YELLOW);
					Y_Voltage_Line=Line.ALL_Voltage_Value;					 
				 }
				 if(ADC_Get.Voltage_Value<=13&&ADC_Get.Voltage_Value>10){
						LCD_ShowString(9,3,"13V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"10V",YELLOW,BLACK,12,0);
						Line.ALL_Voltage_Value=114-(((ADC_Get.Voltage_Value-10)/9)*240);
						LCD_DrawLine(X_Voltage_Line,Y_Voltage_Line,X_Voltage_Line+=1,Line.ALL_Voltage_Value,YELLOW);
						Y_Voltage_Line=Line.ALL_Voltage_Value;					 
				 }if(ADC_Get.Voltage_Value<=16&&ADC_Get.Voltage_Value>13){
						LCD_ShowString(9,3,"16V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"13V",YELLOW,BLACK,12,0);
						Line.ALL_Voltage_Value=114-(((ADC_Get.Voltage_Value-13)/9)*240);
						LCD_DrawLine(X_Voltage_Line,Y_Voltage_Line,X_Voltage_Line+=1,Line.ALL_Voltage_Value,YELLOW);
						Y_Voltage_Line=Line.ALL_Voltage_Value;					 
				 }if(ADC_Get.Voltage_Value<=21&&ADC_Get.Voltage_Value>16){
						LCD_ShowString(9,3,"21V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"16V",YELLOW,BLACK,12,0);
						Line.ALL_Voltage_Value=114-(((ADC_Get.Voltage_Value-16)/15)*240);
						LCD_DrawLine(X_Voltage_Line,Y_Voltage_Line,X_Voltage_Line+=1,Line.ALL_Voltage_Value,YELLOW);
						Y_Voltage_Line=Line.ALL_Voltage_Value;					 
				 }
			//��������
        if(Time_Change_FLAG==8 && ADC_Get.Current_Value<=0.5){ //����0-0.5A ����
					if(C_Range.Current_Range_Flag_one== 0){
						C_Range.Current_Range_Flag_tow=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_three=0;	
						C_Range.Current_Range_Flag_five=0;	
						C_Range.Current_Range_Flag_six=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;						
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213-12,3,"0.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-(ADC_Get.Current_Value*195);
					C_Range.Current_Range_Flag_one=1;					  				
				}else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>0.5 && ADC_Get.Current_Value<=1)){//����0.5-1A ����
					if(C_Range.Current_Range_Flag_tow== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_five=0;	
						C_Range.Current_Range_Flag_six=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"1A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-0.5)*195);
					C_Range.Current_Range_Flag_tow=1;					  													
				}
				//*******************************1-1.5A��������************************************************				
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>1 && ADC_Get.Current_Value<=1.5)){//����1-1.5A ����
					if(C_Range.Current_Range_Flag_five== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_six=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;						
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213-12,3,"1.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-1)*195);
					C_Range.Current_Range_Flag_five=1;					  													
				}
				//*******************************1.5-2A��������************************************************
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>1.5 && ADC_Get.Current_Value<=2)){
					if(C_Range.Current_Range_Flag_six== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_five=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"2A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-1.5)*195);
					C_Range.Current_Range_Flag_six=1;					  													
				}
				//*******************************2-2.5A��������************************************************
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>2 && ADC_Get.Current_Value<=2.5)){
					if(C_Range.Current_Range_Flag_seven== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_five=0;
						C_Range.Current_Range_Flag_six=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213-12,3,"2.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-2)*195);
					C_Range.Current_Range_Flag_seven=1;					  													
				}				
				//*******************************2.5-3A��������************************************************
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>2.5 && ADC_Get.Current_Value<=3)){
					if(C_Range.Current_Range_Flag_eight== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_five=0;
						C_Range.Current_Range_Flag_six=0;	
						C_Range.Current_Range_Flag_seven=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"3A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-2.5)*195);
					C_Range.Current_Range_Flag_eight=1;					  													
				}
//*******************************3-3.5A��������************************************************
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>3 && ADC_Get.Current_Value<=3.5)){
					if(C_Range.Current_Range_Flag_nine== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_five=0;
						C_Range.Current_Range_Flag_six=0;	
						C_Range.Current_Range_Flag_seven=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_eight=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213+12,3,"3.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-3)*195);
					C_Range.Current_Range_Flag_nine=1;					  													
				}		
//*******************************3-3.5A��������************************************************
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>3.5 && ADC_Get.Current_Value<=4)){
					if(C_Range.Current_Range_Flag_ten== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_tow=0;	
						C_Range.Current_Range_Flag_five=0;
						C_Range.Current_Range_Flag_six=0;	
						C_Range.Current_Range_Flag_seven=0;
						C_Range.Current_Range_Flag_nine=0;	
						C_Range.Current_Range_Flag_eight=0;
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"4A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}					
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-3.5)*195);
					C_Range.Current_Range_Flag_ten=1;					  													
				}					
				else if(Time_Change_FLAG==8 && (ADC_Get.Current_Value>4 && ADC_Get.Current_Value<=5)){				
					if(C_Range.Current_Range_Flag_three== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_tow=0;
						C_Range.Current_Range_Flag_four=0;
						C_Range.Current_Range_Flag_five=0;	
						C_Range.Current_Range_Flag_six=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;	
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;						
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}	
					Line.ALL_Current_Value=117-((ADC_Get.Current_Value-3)*46);
					C_Range.Current_Range_Flag_three=1;
				}
				else if(Time_Change_FLAG!=8){				
					if(C_Range.Current_Range_Flag_four== 0){
						C_Range.Current_Range_Flag_one=0;
						C_Range.Current_Range_Flag_tow=0;
						C_Range.Current_Range_Flag_three=0;
						C_Range.Current_Range_Flag_five=0;	
						C_Range.Current_Range_Flag_six=0;
						C_Range.Current_Range_Flag_seven=0;	
						C_Range.Current_Range_Flag_eight=0;
						C_Range.Current_Range_Flag_ten=0;	
						C_Range.Current_Range_Flag_nine=0;						
						LCD_Fill(212-12,2,240,15,BLACK);
						LCD_Fill(212,118,240,135,BLACK);						
						//��ʾ��С��ѹ����	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
					}
          if(ADC_Get.Current_Value>3){					
						Line.ALL_Current_Value=117-(ADC_Get.Current_Value*19);
					}else if(ADC_Get.Current_Value<=3){
						Line.ALL_Current_Value=117-(ADC_Get.Current_Value*31.66);						
					}
					C_Range.Current_Range_Flag_four=1;
				}
				
				
				LCD_DrawLine(X_Current_Line,Y_Current_Line,X_Current_Line+=1,Line.ALL_Current_Value,BLUE);
				Y_Current_Line=Line.ALL_Current_Value;
				X_Line_Loop_FLAG=0;
		}
	}
}
/*-------------------------------------------------------------
*���ܣ������˵���->��ѹ�����߽�����ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_Voltage_Line_Menu(void){
	//��ʾ��ǰ��ѹ�͵���
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	//��ʾ��ѹ 
	LCD_ShowFloatNum1(108,3,  ADC_Get.Voltage_Value,5,YELLOW,BLACK,12);
	LCD_ShowString(144,3,"V",YELLOW,BLACK,12,0);
	if(Begin_Stop_Ri_Flag==0){
  //��ʾ�Ʋ���ѹ
	  if(Voltage_Ripple_Nember>=97){
			Voltage_Ripple_Nember=13;
			LCD_Fill(156,18,234,116,BLACK);			
		}
    ADC_Max_Min=ADC_Sun_Value*1000;
		LCD_ShowFloatNum(171,Voltage_Ripple_Nember+=12,ADC_Max_Min,5,YELLOW,BLACK,12);
		LCD_ShowString(210,Voltage_Ripple_Nember,"mV",YELLOW,BLACK,12,0);
	
	if( ADC_GET_V_X>=150){
						ADC_GET_V_X=10;
						LCD_Fill(0,17,150,119,BLACK);
						menu_Ui_main_Line_Wen(BRRED);
						//LCD_ShowString(177,3,"Ripple",GREEN,BLACK,12,0); 
						//LCD_DrawRectangle(155, 17, 235, 117,GREEN);	
						LCD_ShowString(120,119,"200us",GREEN,BLACK,12,0);		
          if(Voltage_range_Flag==1){
						LCD_ShowString(9,3,"+0.05V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-0.05V",YELLOW,BLACK,12,0);						
					}
					if(Voltage_range_Flag_Tow==1){
						LCD_ShowString(9,3,"+0.1V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-0.1V",YELLOW,BLACK,12,0);
					}
					if(Voltage_range_Flag_Three==1){
						LCD_ShowString(9,3,"+1V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-1V",YELLOW,BLACK,12,0);
					}
		}
	//���õ�ѹ����
		if(ADC_Sun_Value<=0.05){
					CH_Y=100-(ADC_Sun_Value*1200);
					//��ʾ����ѹ��С��ѹ
			    if(Voltage_range_Flag==0){
						Voltage_range_Flag_Three=0;
						Voltage_range_Flag_Tow=0;
						LCD_Fill(8,2,90,15,BLACK);
						LCD_Fill(8,118,90,131,BLACK);
						LCD_ShowString(9,3,"+0.05V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-0.05V",YELLOW,BLACK,12,0);
					}
			    Voltage_range_Flag=1;
		}else if(ADC_Sun_Value>0.05 && ADC_Sun_Value<=0.1){

					CH_Y=100-(ADC_Sun_Value*600);
					//��ʾ����ѹ��С��ѹ
			    if(Voltage_range_Flag_Tow==0){
						Voltage_range_Flag_Three=0;
			      Voltage_range_Flag=0;
						LCD_Fill(8,2,90,15,BLACK);
						LCD_Fill(8,118,90,131,BLACK);
						LCD_ShowString(9,3,"+0.1V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-0.1V",YELLOW,BLACK,12,0);
					}			
			    Voltage_range_Flag_Tow=1;
		}else if(ADC_Sun_Value>0.1 && ADC_Sun_Value<=1){
					CH_Y=100-(ADC_Sun_Value*60);	
					if(Voltage_range_Flag_Three==0){
						LCD_Fill(8,2,90,15,BLACK);
						LCD_Fill(8,118,90,131,BLACK);
						Voltage_range_Flag=0;
						Voltage_range_Flag_Tow=0;
						LCD_ShowString(9,3,"+1V",YELLOW,BLACK,12,0);
						LCD_ShowString(9,119,"-1V",YELLOW,BLACK,12,0);
					}			
			    Voltage_range_Flag_Three=1;
		}

		LCD_DrawLine( ADC_GET_V_X, ADC_GET_V_Y,ADC_GET_V_X++,CH_Y,YELLOW);				
		ADC_GET_V_Y=CH_Y;						
  }
}
/*-------------------------------------------------------------
*���ܣ������˵���->���¹��ؽ�����ʾ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_Current_Temp_protect(void){
  //��ʾ����
  LCD_ShowChinese16x16(4,3,"��",WHITE,BLACK,16,0);
  LCD_ShowChinese16x16(4+16,3,"��",WHITE,BLACK,16,0);	
	LCD_ShowChinese16x16(4+32,3,"��",WHITE,BLACK,16,0);
	ADC_Get.Current_Value=ADC_Read_current_Value_average();//0.0399
	LCD_ShowFloatNum1(54,3,	ADC_Get.Current_Value,5,BLUE,BLACK,16);
	LCD_ShowString(94+8,3,"A",BLUE,BLACK,16,0);
  //��ʾ�¶�	
	LCD_ShowChinese16x16(129,3,"��",WHITE,BLACK,16,0);
  LCD_ShowChinese16x16(128+16,3,"��",WHITE,BLACK,16,0);	

  AHT10_Read_Humi_Temp(&AHT10.humi,&AHT10.temp);
	ALL_temp=((AHT10.temp/100)*10)+(AHT10.temp%100/10);
	sprintf(temp_char,"%d%d.%dC",AHT10.temp/100,AHT10.temp%100/10,AHT10.temp%100%10);
	LCD_ShowString(168,3,temp_char,RED,BLACK,16,0);
	//�����
  LCD_ShowChinese16x16(4,19,"��",GREEN,BLACK,16,0);
  LCD_ShowChinese16x16(4+16,19,"��",GREEN,BLACK,16,0);	
	LCD_ShowChinese16x16(4+32,19,"��",GREEN,BLACK,16,0);
	
	LCD_ShowFloatNum1(54,19,C_T_P.protect_Current,5,PINK_RED,BLACK,16);
	LCD_ShowString(94+8,19,"A",PINK_RED,BLACK,16,0);
  //���¶�	
	LCD_ShowChinese16x16(129,19,"��",RED,BLACK,16,0);
  LCD_ShowChinese16x16(128+16,19,"��",RED,BLACK,16,0);
	LCD_ShowFloatNum(168,19,C_T_P.protect_Temp,3,RED_NOW,BLACK,16);
	LCD_ShowString(168+33,19,"C",RED_NOW,BLACK,16,0);
	
}
/*-------------------------------------------------------------
*���ܣ��ļ��˵���->PD��ƭ����
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_PD_Voltage_Current(void){
  ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	//��ʾ��ѹ 36*36
	LCD_ShowFloatNum1(30,18,  ADC_Get.Voltage_Value,5,YELLOW,BLACK,16);
	LCD_ShowString(78,19,"V",YELLOW,BLACK,16,0);
  
	//��ʾ���� 36*36	
	ADC_Get.Current_Value=ADC_Read_current_Value_average();//0.0399
	LCD_ShowFloatNum1(138+8,18,	ADC_Get.Current_Value,5,BLUE,BLACK,16);
	LCD_ShowString(138+48+8,18,"A",BLUE,BLACK,16,0);			
		
		
}
/*-------------------------------------------------------------
*���ܣ��ļ��˵���->QC��ƭ����
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void menu_Ui_QC_Voltage_Current(void){
ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	//��ʾ��ѹ 36*36
	LCD_ShowFloatNum1(30,18,  ADC_Get.Voltage_Value,5,YELLOW,BLACK,16);
	LCD_ShowString(78,19,"V",YELLOW,BLACK,16,0);
  
	//��ʾ���� 36*36	
	ADC_Get.Current_Value=ADC_Read_current_Value_average();//0.0399
	LCD_ShowFloatNum1(138+8,18,	ADC_Get.Current_Value,5,BLUE,BLACK,16);
	LCD_ShowString(138+48+8,18,"A",BLUE,BLACK,16,0);


  //��ʾD+��D-��ѹ
	LCD_ShowString(132,86,"D+",PINK_RED,BLACK,16,0);
	LCD_ShowString(132,86+6+16,"D-",RED_NOW,BLACK,16,0);
	//D+
	ADC_Get.D_LEFT_Voltage_Value=ADC_D_LEFT_Read_Value_average();
	LCD_ShowFloatNum1(132+20,86,ADC_Get.D_LEFT_Voltage_Value,5,YELLOW,BLACK,16);
	LCD_ShowString(200,86,"V",YELLOW,BLACK,16,0);
	//D-
	ADC_Get.D_RIGHT_Voltage_Value=ADC_D_RIGHT_Read_Value_average();
	LCD_ShowFloatNum1(132+20,86+6+16,ADC_Get.D_RIGHT_Voltage_Value,5,YELLOW,BLACK,16);
	LCD_ShowString(200,86+6+16,"V",YELLOW,BLACK,16,0);
}