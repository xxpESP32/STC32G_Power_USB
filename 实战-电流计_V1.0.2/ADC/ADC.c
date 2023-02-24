/*
*ע�⣺ʹ��keil��Ҫ����ΪGB2312
*==============================ADC����Դ�ļ�=======================
*-------------------------------------------------------------------
*�ļ��޸���ʷ
*<ʱ��>    | <�汾>  | <����>  | <����>  
*2023.2.24 | V1.0.2   | С��    | ����ѹ����������D+��D-��ADC����
*-------------------------------------------------------------------
*����Ҫ��ѧ�뵽CSDN��������"��Ƭ�л���"��STC32Gר��
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
*���ܣ�����ѹ��ADC������ʼ������
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
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
*���ܣ�����ѹ��ADC����12��������ֵ����Сֵ����λֵƽ���˲��㷨���������ѹ��
*ͬʱ���÷ֵ���㡣
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
float ADC_Voltage_Read_Value_average(void){
//	VOL_dat=0;
//	VOL_dat=((ADC_Voltage_Read_Value()*2.5)/4096L)*11.214;
	ADC_Max_Value=VOL_dat;
	ADC_Min_Value=VOL_dat;
	Voltage_SUM=0;
	for(ins=0;ins<12;ins++){
		VOL_dat_SUM=(ADC_Voltage_Read_Value()*2.5)/4059L;
		if(VOL_dat_SUM<=0.307){//7V����
			VOL_dat=VOL_dat_SUM*22.229;
		}else if(VOL_dat_SUM>0.307 && VOL_dat_SUM<=0.394){//7V-9V
			VOL_dat=VOL_dat_SUM*22.600;
		}else if(VOL_dat_SUM>0.394 && VOL_dat_SUM<=0.523){//9V-12V
			VOL_dat=VOL_dat_SUM*22.650;
		}else if(VOL_dat_SUM>0.523 && VOL_dat_SUM<=0.653){//12V-15V
			VOL_dat=VOL_dat_SUM*22.700;
		}else if(VOL_dat_SUM>0.653 && VOL_dat_SUM<=0.780){//15V-18V
			VOL_dat=VOL_dat_SUM*22.750;
		}else if(VOL_dat_SUM>0.780){//18V����
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
*���ܣ����߿���ˢ�»�ȡ��ѹ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
float ADC_Voltage_Read_Value_Line(void){
		VOL_dat_SUM=(ADC_Voltage_Read_Value()*2.5)/4059L;
		if(VOL_dat_SUM<=0.307){//7V����
			VOL_dat=VOL_dat_SUM*22.229;
		}else if(VOL_dat_SUM>0.307 && VOL_dat_SUM<=0.394){//7V-9V
			VOL_dat=VOL_dat_SUM*22.600;
		}else if(VOL_dat_SUM>0.394 && VOL_dat_SUM<=0.523){//9V-12V
			VOL_dat=VOL_dat_SUM*22.650;
		}else if(VOL_dat_SUM>0.523 && VOL_dat_SUM<=0.653){//12V-15V
			VOL_dat=VOL_dat_SUM*22.700;
		}else if(VOL_dat_SUM>0.653 && VOL_dat_SUM<=0.780){//15V-18V
			VOL_dat=VOL_dat_SUM*22.750;
		}else if(VOL_dat_SUM>0.780){//18V����
			VOL_dat=VOL_dat_SUM*22.800;
		}
	return VOL_dat;	
}
/*-------------------------------------------------------------
*���ܣ�ina199������ADC������ʼ������
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
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
*���ܣ������Ĳ���
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
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
*���ܣ�C+��ѹ��ADC������ʼ������
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
*-------------------------------------------------------------*/
//��ȡD+���ŵ�ѹ
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
*���ܣ�D+��ADC����
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
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
*���ܣ�D-��ADC������ʼ������
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
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
*���ܣ�D-��ADC����
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο���<STC32G�����ֲ�>
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