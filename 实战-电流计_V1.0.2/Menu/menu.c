/*
*ע�⣺ʹ��keil��Ҫ����ΪGB2312
*==============================�༶�˵�����Դ�ļ�=======================
*-------------------------------------------------------------------
*�ļ��޸���ʷ
*<ʱ��>    | <�汾>  | <����>  | <����>  
*2023.2.24 | V1.0.2   | С��    | �༶�˵���������������
*-------------------------------------------------------------------
*/

#include "menu.h"
#include "menu_Ui.h"
u8 index_cp;
void (*current_operation_func)(void);

static void menu_part_main(void);

static void menu_part_one(void);
static void menu_part_tow(void);
static void menu_part_three(void);
static void menu_part_four(void);

static void menu_part_one_one(void);
static void menu_part_one_tow(void);
static void menu_part_one_three(void);

static void menu_part_tow_one(void);

static void menu_part_three_one(void);

static void menu_part_four_one(void);
static void menu_part_four_one_one(void);
static void menu_part_four_one_tow(void);
static void menu_part_four_one_threen(void);

static void menu_part_one_one_one(void);
static void menu_part_one_one_tow(void);
static void menu_part_one_one_three(void);
static void menu_part_one_one_four(void);
static void menu_part_one_one_five(void);

static void menu_part_one_tow_one(void);
static void menu_part_one_tow_tow(void);
static void menu_part_one_tow_three(void);
static void menu_part_one_tow_four(void);


Menu_Creat M_G[25]={
		{0,1,1,0,(*menu_part_main)}, //��һ��
		
		{1,2,5,0,(*menu_part_one)}, //�ڶ���	
		{2,3,8,0,(*menu_part_tow)}, //�ڶ���	
		{3,4,9,0,(*menu_part_three)}, //�ڶ���	
		{4,1,10,0,(*menu_part_four)}, //�ڶ���	

		{5,6,14,1,(*menu_part_one_one)}, //������	
		{6,7,19,1,(*menu_part_one_tow)}, //������	
		{7,5,7,1,(*menu_part_one_three)}, //������	

		{8,8,8,2,(*menu_part_tow_one)}, //������
		
    {9,9,9,3,(*menu_part_three_one)}, //������  

    {10,11,10,4,(*menu_part_four_one)}, //������ ������ѹ���� 
    {11,12,11,4,(*menu_part_four_one_one)}, //������ ����+100ma 
		{12,13,12,4,(*menu_part_four_one_tow)}, //������ ����-100ma 
		{13,10,13,4,(*menu_part_four_one_threen)}, //������ �¶�+1C 
		
		{14,15,14,5,(*menu_part_one_one_one)},		
		{15,16,15,5,(*menu_part_one_one_tow)},
 		{16,17,16,5,(*menu_part_one_one_three)},
		{17,18,17,5,(*menu_part_one_one_four)},
		{18,15,18,5,(*menu_part_one_one_five)},

		{19,20,19,6,(*menu_part_one_tow_one)},
		{20,21,19,6,(*menu_part_one_tow_tow)},
		{21,22,19,6,(*menu_part_one_tow_three)},
		{22,19,19,6,(*menu_part_one_tow_four)},		
};

void Menu_Loop(void){
			current_operation_func=M_G[index_cp].current_operation;

      current_operation_func();	
	
}

static void menu_part_main(void){
	menu_Ui_main();
	
}

static void menu_part_one(void){
	menu_Ui_Choose_Menu(0);
}

static void menu_part_tow(void){
	menu_Ui_Choose_Menu(1);	
}

static void menu_part_three(void){
	menu_Ui_Choose_Menu(2);	
}

static void menu_part_four(void){
	menu_Ui_Choose_Menu(3);	
}

static void menu_part_one_one(void){
	menu_Ui_PD_QC_Menu(0);
}

static void menu_part_one_tow(void){
	menu_Ui_PD_QC_Menu(1);
}

static void menu_part_one_three(void){
	menu_Ui_PD_QC_Menu(2);
}

static void menu_part_tow_one(void){
		menu_Ui_Voltage_current_Line_Menu();
}

static void menu_part_three_one(void){
		menu_Ui_Voltage_Line_Menu();	
}

static void menu_part_four_one(void){
		menu_Ui_Current_Temp_protect();	
}

static void menu_part_four_one_one(void){
	menu_Ui_Current_Temp_protect();
}

static void menu_part_four_one_tow(void){
	menu_Ui_Current_Temp_protect();
}

static void menu_part_four_one_threen(void){
	menu_Ui_Current_Temp_protect();
}

static void menu_part_one_one_one(void){
	menu_Ui_PD_Voltage_Current();
}
static void menu_part_one_one_tow(void){
	menu_Ui_PD_Voltage_Current();	
}

static void menu_part_one_one_three(void){
	menu_Ui_PD_Voltage_Current();		
}

static void menu_part_one_one_four(void){
	menu_Ui_PD_Voltage_Current();		
}

static void menu_part_one_one_five(void){
	menu_Ui_PD_Voltage_Current();		
}
static void menu_part_one_tow_one(void){
	menu_Ui_QC_Voltage_Current();	
}
static void menu_part_one_tow_tow(void){
	menu_Ui_QC_Voltage_Current();	
}
static void menu_part_one_tow_three(void){
	menu_Ui_QC_Voltage_Current();	
}
static void menu_part_one_tow_four(void){
	menu_Ui_QC_Voltage_Current();	
}
