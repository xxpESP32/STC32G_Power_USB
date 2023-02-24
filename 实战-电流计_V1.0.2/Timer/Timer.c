/*
*注意：使用keil需要设置为GB2312
*==============================Timer定时器源文件=======================
*-------------------------------------------------------------------
*文件修改历史
*<时间>    | <版本>  | <作者>  | <功能>  
*2023.2.24 | V1.0.2   | 小夏    | Timer定时器配置
*-------------------------------------------------------------------
*如需要教学请到CSDN上面搜索"单片有机机"的STC32G专栏
*/

#include "Timer.h"
#include "ADC.h"
#include "I2C.h"
#include "AHT10.h"
#include "menu_Ui.h"
#include "KEY.h"
u16 time;
u16 T1_time;
u16 Change_Time =60000;
u16 X_Voltage_Line=11;
u16 Y_Voltage_Line=114;

u16 X_Current_Line=10;
u16 Y_Current_Line=117;
u8 X_Line_Loop_FLAG;
u8 Dispaly_Ch_Flag;
u16 Timer2_flag;
unsigned long time_nember;
Time_Display T_D;
float umA_Num;
float umA_Num_Sum;
float uW_Num;
float uW_Num_Sum;
/*-------------------------------------------------------------
*功能：Timer0中断服务函数配置（电压电流曲线时间设置）
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void TM0_Isr() interrupt 1
{	
  
	time++;
	if(time>=Change_Time){ //22ms

		if(FLAGS==1){
      X_Line_Loop_FLAG=1;
		}
		time=0;
	}

	
}
/*-------------------------------------------------------------
*功能：Timer0初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void Timer0_Init(void){
	
	TMOD=0x00; //16位自动重装载值
	TL0=62623;  //定时20ms
	TH0=62623>>8;  
	TR0=1;  //开启timer0定时器
	ET0=1;  //开启timer0中断
	EA=1;   //开启总中断
	
}
/*-------------------------------------------------------------
*功能：Timer1中断服务函数配置（检测AH，WH，时间功耗）
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void TM1_Isr() interrupt 3
{
		Timer2_flag++;
	if(Timer2_flag>=1000 && ADC_Get.Current_Value>=0.006){
		time_nember++;
		T_D.S=time_nember;
		//T_D.M=time_nember/60;	
		//T_D.H=time_nember/3600;
		if(T_D.S>=60){
			T_D.M++;
			time_nember=0;
		}
		if(T_D.M>=60){
			T_D.H++;
			T_D.M=0;
		}
		umA_Num=(ADC_Get.Current_Value/3600);
		umA_Num_Sum+=umA_Num;
		uW_Num=umA_Num*ADC_Get.Voltage_Value;
		uW_Num_Sum+=uW_Num;
		Timer2_flag=0;	
	}
	
	
}
/*-------------------------------------------------------------
*功能：Timer1初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void Timer1_Init(void){
	
	TMOD=0x00; //16位自动重装载值
	TL1=62623;  //定时1ms
	TH1=62623>>8;  
	TR1=1;  //开启timer0定时器
	ET1=1;  //开启timer0中断
	EA=1;   //开启总中断	
	
	
}
/*-------------------------------------------------------------
*功能：Timer2中断服务函数配置（检测过流过温）
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void TM2_Isr() interrupt 12
{

	
		T1_time++;
	if(T1_time>=1){
		if(C_T_P.protect_Current<=ADC_Get.Current_Value){//过流保护
			Dispaly_Ch_Flag=1;
			P16=0;
		}else if(C_T_P.protect_Temp<=ALL_temp){//过温保护
			Dispaly_Ch_Flag=2;
			P16=0;
			
		}
		if(KEY_BACK_Read==0){
					P16=1;
					Dispaly_Ch_Flag=0;			
			}
		T1_time=0;
						
	}
}
/*-------------------------------------------------------------
*功能：Timer2初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------*/
void Timer2_Init(void){
	//TMOD=0x00; //16位自动重装载值	
	T2L=62623;  //定时20ms
	T2H=62623>>8;  
	T2R=1;  //开启timer0定时器
	ET2=1;  //开启timer0中断
	EA=1;   //开启总中断		
	
}