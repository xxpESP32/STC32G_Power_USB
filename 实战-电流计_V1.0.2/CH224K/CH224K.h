#ifndef __CH224K_H
#define __CH224K_H
#include <STC32G.H>
#include "system.h"

#define CFG1 P27
#define CFG2 P26
#define CFG3 P20

enum OUTPUT_Volage{
	 OUTPUT_5V =1,
	 OUTPUT_9V,
   OUTPUT_12V,
   OUTPUT_15V,
   OUTPUT_20V
	
};
extern enum OUTPUT_Volage OUTPUT_Volage_Value;

typedef struct{
	u8 PD_9V_Flag;
	u8 PD_12V_Flag;	
	u8 PD_15V_Flag;	
	u8 PD_20V_Flag;
}PD_Voltage_Get;
extern PD_Voltage_Get PD_Get;
extern u8 PD_Power_FLAG;
void CH224K_PD_Voltage(u8 V_FLag);
void PD_Bgegin(void);
void PD_Power_Output(void);
#endif