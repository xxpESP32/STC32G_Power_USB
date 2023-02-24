/*
*注意：使用keil需要设置为GB2312
*==============================ADC采样源文件=======================
*-------------------------------------------------------------------
*文件修改历史
*<时间>    | <版本>  | <作者>  | <功能>  
*2023.2.24 | V1.0.2   | 小夏    | 主电压、主电流、D+，D-的ADC采样
*-------------------------------------------------------------------
*如需要教学请到CSDN上面搜索"单片有机机"的STC32G专栏
*/

#include "ADC.h"

float dat=0;
u16 current_dat;


float current_ALL;
int i;
int ins;
float VOL_dat;
float VOL_dat_SUM;
int ADC_Loop;

float ADC_Max_Value;
float ADC_Min_Value;
float ADC_Sun_Value;
float VOL_dat_SUM;

float D_Left_dats;
float D_Left_Value;
float D_LEFT_dat;

float D_RIGHT_dats;
float D_RIGHT_Value;
float D_RIGHT_dat;

float Voltage_SUM;
float Voltage_SUM_average;


void ADC_Init(void){
//	P0M1 = 0x00;   
//	P0M0 = 0x01;
	//ADC_CONTR = 0x0A;
	ADC_CONTR = 0x0A;
	ADCTIM = 0xFF;
	ADCCFG = 0x20;
	
	ADC_POWER=1;	
}

/*-------------------------------------------------------------
*功能：主电压的ADC采样初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
float ADC_Voltage_Read_Value(void){
	ADC_CONTR = 0x0A;
  ADC_POWER=1;
	ADC_START = 1;
	while(!ADC_FLAG);
	ADC_FLAG=0;
	dat =(ADC_RES<<8)|ADC_RESL;

	return dat;
}
/*-------------------------------------------------------------
*功能：主电压的ADC采样12次求出最大值和最小值（中位值平均滤波算法）求出主电压。
*同时采用分点计算。
*作者：小夏
*修改时间：2023.2.24
*参考：大脑（自己）
*-------------------------------------------------------------*/
float ADC_Voltage_Read_Value_average(void){
//	VOL_dat=0;
//	VOL_dat=((ADC_Voltage_Read_Value()*2.5)/4096L)*11.214;
	ADC_Max_Value=VOL_dat;
	ADC_Min_Value=VOL_dat;
	Voltage_SUM=0;
	for(ins=0;ins<12;ins++){
		VOL_dat_SUM=(ADC_Voltage_Read_Value()*2.5)/4059L;
		if(VOL_dat_SUM<=0.307){//7V以下
			VOL_dat=VOL_dat_SUM*22.229;
		}else if(VOL_dat_SUM>0.307 && VOL_dat_SUM<=0.394){//7V-9V
			VOL_dat=VOL_dat_SUM*22.600;
		}else if(VOL_dat_SUM>0.394 && VOL_dat_SUM<=0.523){//9V-12V
			VOL_dat=VOL_dat_SUM*22.650;
		}else if(VOL_dat_SUM>0.523 && VOL_dat_SUM<=0.653){//12V-15V
			VOL_dat=VOL_dat_SUM*22.700;
		}else if(VOL_dat_SUM>0.653 && VOL_dat_SUM<=0.780){//15V-18V
			VOL_dat=VOL_dat_SUM*22.750;
		}else if(VOL_dat_SUM>0.780){//18V以上
			VOL_dat=VOL_dat_SUM*22.800;
		}
		if(VOL_dat>ADC_Max_Value){
			ADC_Max_Value=VOL_dat;
      
		}
		else if(VOL_dat<ADC_Min_Value){
			ADC_Min_Value=VOL_dat;

		}
	  Voltage_SUM+=VOL_dat;
	}	
	ADC_Sun_Value=ADC_Max_Value-ADC_Min_Value;
  Voltage_SUM_average=(Voltage_SUM-ADC_Max_Value-ADC_Min_Value)/10;
	return Voltage_SUM_average;
	
}
/*-------------------------------------------------------------
*功能：曲线快速刷新获取电压
*作者：小夏
*修改时间：2023.2.24
*参考：大脑（自己）
*-------------------------------------------------------------*/
float ADC_Voltage_Read_Value_Line(void){
		VOL_dat_SUM=(ADC_Voltage_Read_Value()*2.5)/4059L;
		if(VOL_dat_SUM<=0.307){//7V以下
			VOL_dat=VOL_dat_SUM*22.229;
		}else if(VOL_dat_SUM>0.307 && VOL_dat_SUM<=0.394){//7V-9V
			VOL_dat=VOL_dat_SUM*22.600;
		}else if(VOL_dat_SUM>0.394 && VOL_dat_SUM<=0.523){//9V-12V
			VOL_dat=VOL_dat_SUM*22.650;
		}else if(VOL_dat_SUM>0.523 && VOL_dat_SUM<=0.653){//12V-15V
			VOL_dat=VOL_dat_SUM*22.700;
		}else if(VOL_dat_SUM>0.653 && VOL_dat_SUM<=0.780){//15V-18V
			VOL_dat=VOL_dat_SUM*22.750;
		}else if(VOL_dat_SUM>0.780){//18V以上
			VOL_dat=VOL_dat_SUM*22.800;
		}
	return VOL_dat;	
}
/*-------------------------------------------------------------
*功能：ina199电流的ADC采样初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
float ADC_Read_current_Value(void){
	  ADC_CONTR = 0x0B;
	  ADC_POWER=1;	
		ADC_START = 1;
	//	Delay_ms(2);
		while(!ADC_FLAG);
		ADC_FLAG=0;
		current_dat =(ADC_RES<<8)|ADC_RESL;
   
	return current_dat;
}
/*-------------------------------------------------------------
*功能：电流的采样
*作者：小夏
*修改时间：2023.2.24
*参考：大脑（自己）
*-------------------------------------------------------------*/
float ADC_Read_current_Value_average(void){
	current_ALL =0;
	for(ins=0;ins<3;ins++){
		current_ALL+=ADC_Read_current_Value();

	}
	current_ALL=current_ALL/3;
	current_ALL=((current_ALL*2.5)/4096L)*1.794-0.080;
	if(current_ALL<=-0&&current_ALL>-1000|current_ALL==0){
		current_ALL=0;
	}
	return current_ALL;
}
/*-------------------------------------------------------------
*功能：C+电压的ADC采样初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
//读取D+引脚电压
float ADC_Read_D_LEFT_Value(void){
	  ADC_CONTR = 0x09;
	  ADC_POWER=1;	
		ADC_START = 1;
		while(!ADC_FLAG);
		ADC_FLAG=0;
		D_Left_dats =(ADC_RES<<8)|ADC_RESL;
   
	return D_Left_dats;
}
/*-------------------------------------------------------------
*功能：D+的ADC采样
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
float ADC_D_LEFT_Read_Value_average(void){
	

		D_Left_Value=(ADC_Read_D_LEFT_Value()*2.5)/4059L;
	  if(D_Left_Value>0.100){
			D_LEFT_dat=D_Left_Value*21.5;
		}else{
			D_LEFT_dat=D_Left_Value*17.098; 
		}
	return D_LEFT_dat;	
}
/*-------------------------------------------------------------
*功能：D-的ADC采样初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
float ADC_Read_D_RIGHT_Value(void){
	  ADC_CONTR = 0x08;
	  ADC_POWER=1;	
		ADC_START = 1;
		while(!ADC_FLAG);
		ADC_FLAG=0;
		D_RIGHT_dats =(ADC_RES<<8)|ADC_RESL;
   
	return D_RIGHT_dats;
}
/*-------------------------------------------------------------
*功能：D-的ADC采样
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G技术手册>
*-------------------------------------------------------------*/
float ADC_D_RIGHT_Read_Value_average(void){
	

		D_RIGHT_Value=(ADC_Read_D_RIGHT_Value()*2.5)/4059L;
	  if(D_RIGHT_Value>0.100){
			D_RIGHT_dat=D_RIGHT_Value*21.5;			
		}else{
			D_RIGHT_dat=D_RIGHT_Value*17.098;
		}
 
	return D_RIGHT_dat;	
}