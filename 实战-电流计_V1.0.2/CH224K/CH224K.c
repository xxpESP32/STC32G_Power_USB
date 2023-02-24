/*
*ע�⣺ʹ��keil��Ҫ����ΪGB2312
*==============================CH224KPD��QC��ƭԴ�ļ�=======================
*-------------------------------------------------------------------
*�ļ��޸���ʷ
*<ʱ��>    | <�汾>  | <����>  | <����>  
*2023.2.24 | V1.0.2   | С��    | CH224KPD��QC��ƭ
*-------------------------------------------------------------------
*/

#include "CH224K.h"
#include "menu_Ui.h"
#include "ADC.h"
u8 PD_Power_FLAG;
PD_Voltage_Get PD_Get;
/*-------------------------------------------------------------
*���ܣ�CH224K��PD��QC��ͬ��ѹ��ƭ
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void CH224K_PD_Voltage(u8 V_FLag){
	
	if(V_FLag ==OUTPUT_5V){
		CFG1=1;
		CFG2=0;
		CFG3=0;		
	}else if(V_FLag ==OUTPUT_9V){
		CFG1=0;
		CFG2=0;
		CFG3=0;			
	}else if(V_FLag ==OUTPUT_12V){
		CFG1=0;
		CFG2=0;
		CFG3=1;			
	}else if(V_FLag ==OUTPUT_15V){
		CFG1=0;
		CFG2=1;
		CFG3=1;			
	}else if(V_FLag ==OUTPUT_20V){
		CFG1=0;
		CFG2=1;
		CFG3=0;			
	}
	
}
/*-------------------------------------------------------------
*���ܣ�CH224K��PD��QC��ͬ��ѹ���
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void PD_Bgegin(void){
	//���9V
	CH224K_PD_Voltage(OUTPUT_9V);
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	if(ADC_Get.Voltage_Value>6.8) PD_Get.PD_9V_Flag=1;
	else PD_Get.PD_9V_Flag=0;
	//���12V
	CH224K_PD_Voltage(OUTPUT_12V);
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	if(ADC_Get.Voltage_Value>10.8) PD_Get.PD_12V_Flag=1;
	else PD_Get.PD_12V_Flag=0;	
	//���12V
	CH224K_PD_Voltage(OUTPUT_15V);
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	if(ADC_Get.Voltage_Value>12.8) PD_Get.PD_15V_Flag=1;
	else PD_Get.PD_15V_Flag=0;	
	//���12V
	CH224K_PD_Voltage(OUTPUT_20V);
	ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
	if(ADC_Get.Voltage_Value>16.8) PD_Get.PD_20V_Flag=1;
	else PD_Get.PD_20V_Flag=0;
}
/*-------------------------------------------------------------
*���ܣ�CH224K��PD��QC��ͬ��ѹ��ƭ���
*���ߣ�С��
*�޸�ʱ�䣺2023.2.24
*�ο������ԣ��Լ���
*-------------------------------------------------------------*/
void PD_Power_Output(void){
	if(PD_Get.PD_9V_Flag==0&&PD_Get.PD_12V_Flag==0&&PD_Get.PD_15V_Flag==0&&PD_Get.PD_20V_Flag==0){		
		PD_Power_FLAG =0;		//PD0V
	}
	if(PD_Get.PD_9V_Flag==1&&PD_Get.PD_12V_Flag==1&&PD_Get.PD_15V_Flag==0&&PD_Get.PD_20V_Flag==0){		
		PD_Power_FLAG =1; //PD22W		
	}	
	if(PD_Get.PD_9V_Flag==1&&PD_Get.PD_12V_Flag==0&&PD_Get.PD_15V_Flag==1&&PD_Get.PD_20V_Flag==1){		
		PD_Power_FLAG =2; //PD49.5W		
	}	
	if(PD_Get.PD_9V_Flag==1&&PD_Get.PD_12V_Flag==1&&PD_Get.PD_15V_Flag==1&&PD_Get.PD_20V_Flag==1){		
		PD_Power_FLAG =3; //PD66W		
	}	
}