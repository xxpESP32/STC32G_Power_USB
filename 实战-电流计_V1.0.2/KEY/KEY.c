/*
*注意：使用keil需要设置为GB2312
*==============================按键源文件=======================
*-------------------------------------------------------------------
*文件修改历史
*<时间>    | <版本>  | <作者>  | <功能>  
*2023.2.24 | V1.0.2   | 小夏    | 采用的是轮询方案读取按键（使用按键外部中断是会出现刷新有残影）
*-------------------------------------------------------------------
*/

#include "KEY.h"
#include "menu.h"
#include "LCD.h"
#include "lcd_init.h"
#include "menu_Ui.h"
#include "Timer.h"
#include "Pic.h"
#include "CH224K.h"
u8 Line_x;
u8 sta_x=10;
int Line_y;
u8 Clear_FLAG=0;
u8 nember_Flag;
u8 Time_Change_FLAG;
u8 Begin_Stop_Flag;
u8 Begin_Stop_Ri_Flag;
static void PD_Dislay_Ui(void);

//******************
//----2023.2.1----
//更新内容完善QC诱骗界面
u8 QC_Power_FLAG;
//******************
static void QC_Dislay_Ui(void);
static void Voltage_OUTPUT_5V_Succeed(void);
/*-------------------------------------------------------------
*功能：按键初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<STC32G数据手册>
*-------------------------------------------------------------
*如需要教学请到CSDN上面搜索"单片有机机"的STC32G专栏
*/
void KEY_Init(void){
	
 P2IM0=0x00;	
 P2IM1=0x00;
 P2INTE=0x0e;

 EA=1;	
	
}
/*-------------------------------------------------------------
*功能：按键读取进入多级菜单配置
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Key_EVENT(void){
			if(KEY_LEFT_Read ==0){ //右按键
			Delay_ms(10);
			if(KEY_LEFT_Read ==0){
			Diaplay_Begin_Stop(8); //暂停
			Diaplay_Begin_Stop(9); //暂停				
			index_cp=M_G[index_cp].next;
			if(index_cp!=8 && index_cp!=9 &&index_cp!=10 && index_cp!=11 && index_cp!=12 && index_cp!=13 && index_cp!=15&& index_cp!=16&& index_cp!=17&& index_cp!=18 &&index_cp!=19&&index_cp!=20&& index_cp!=21&& index_cp!=22) LCD_Fill(0,0,240,135,BLACK);
			//Display_main_Line();
		  //Display_main_Line_Voltage();
			Current_Temp_Ui();
			PD_Dislay_Ui();
			QC_Dislay_Ui();
		  }
		}
		if(KEY_ENTER_Read==0){ //确定按键
			Delay_ms(10);
			if(KEY_ENTER_Read==0){
			Current_Temp_add();
			Change_Timer_Time();
			Voltage_OUTPUT_5V_Succeed();
			index_cp=M_G[index_cp].enter; 
			LCD_Fill(0,0,240,135,BLACK);		
			Display_main_Line();
		  Display_main_Line_Voltage();
			Current_Temp_Ui();
		  PD_Dislay_Ui();
			QC_Dislay_Ui();
		}
	  }
		if(KEY_BACK_Read==0){ //返回按键（左按键）
			Delay_ms(10);
			if(KEY_BACK_Read==0){
			Current_Temp_Set_succeed();
			index_cp=M_G[index_cp].back;			   
			 LCD_Fill(0,0,240,135,BLACK);
			
			if(index_cp==0){//显示框图
					menu_Ui_main_Rect_set_steup();			
			}
			Reset_Display_X_Line();//离线曲线
			}
		}	

	
			Menu_Loop();	
	
}
/*
void Key_Nvic_Isr(void) interrupt 39
{
	u8 Key_Gpio=0;
	Key_Gpio =P2INTF;
	
	if(Key_Gpio){
	
		if(Key_Gpio& 0x02){ //右按键
			Delay_ms(50);
			if(KEY_LEFT_Read ==0){
			LCD_Fill(0,0,240,135,BLACK);
			index_cp=M_G[index_cp].next;

 
		  }
		}
		if(Key_Gpio& 0x04){ //确定按键
			Delay_ms(50);
			if(KEY_ENTER_Read==0){
			LCD_Fill(0,0,240,135,BLACK);
			index_cp=M_G[index_cp].enter; 

		
		  if(index_cp==8){
				menu_Ui_main_Line();
			}
		
		}
	  }
		if(Key_Gpio& 0x08){ //返回按键（左按键）
			Delay_ms(50);
			if(KEY_BACK_Read==0){
			Reset_Display_X_Line();

			index_cp=M_G[index_cp].back;			   
			LCD_Fill(0,0,240,135,BLACK);
			
			if(index_cp==0){//显示框图
					menu_Ui_main_Rect_set_steup();			
			}

		}
		}	

	}	
			Menu_Loop();	
P2INTF =0x00;
}
*/

/*-------------------------------------------------------------
*功能：单次显示 menu_Ui_main的框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void menu_Ui_main_Rect_set_steup(void){
	LCD_DrawLine(204,0,204,18,GREEN);
	LCD_DrawRectangle(0, 16, 240, 17,GREEN);
	LCD_DrawRectangle(0, 116, 133, 117,GREEN);	
	LCD_DrawRectangle(132, 117, 133, 135,GREEN);	
	LCD_DrawRectangle(132, 17, 133, 117,GREEN);	
	LCD_DrawRectangle(239, 17, 240, 117,GREEN);	
	LCD_DrawRectangle(239, 116, 240, 135,GREEN);
	
	LCD_DrawRectangle(0, 16, 1, 116,GREEN);	
	LCD_DrawRectangle(132, 57, 240, 58,GREEN);	
	LCD_DrawRectangle(132, 107, 240, 108,GREEN);	
	
}
/*-------------------------------------------------------------
*功能：单次显示显示框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void menu_Ui_main_Line(u16 color){
  for(Line_x=10;Line_x<=220;Line_x+=10){
		LCD_DrawLine(Line_x,17,Line_x,19+99,color);//在指定位置画一条线
	}		
  for(Line_y=17;Line_y<=100+17;Line_y+=10){
		LCD_DrawLine(10,Line_y,220,Line_y,color);//在指定位置画一条线
	}		
	
}
void menu_Ui_main_Line_Wen(u16 color){
  for(Line_x=10;Line_x<=150;Line_x+=10){
		LCD_DrawLine(Line_x,17,Line_x,19+99,color);//在指定位置画一条线
	}		
  for(Line_y=17;Line_y<=100+17;Line_y+=10){
		LCD_DrawLine(10,Line_y,150,Line_y,color);//在指定位置画一条线
	}		
	
}
/*-------------------------------------------------------------
*功能：单次显示曲线的电压电流量程
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Reset_Display_X_Line(void){
	if(index_cp==8){
		FLAGS=0;
		X_Voltage_Line=10;
		X_Current_Line=10;
		LCD_ShowString(9,3,"24V",YELLOW,BLACK,12,0);
		LCD_ShowString(9,119,"0V",YELLOW,BLACK,12,0);
		if(C_Range.Current_Range_Flag_one== 1){					
			//显示最小电压电流	
			LCD_ShowString(213-12,3,"0.5A",BLUE,BLACK,12,0);
			LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_tow== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"1A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_three== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_four== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}			
	}	
}
/*-------------------------------------------------------------
*功能：单次显示曲线的电压电流量程
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Display_main_Line(void){
		if(index_cp==8){
		menu_Ui_main_Line(RED);
		FLAGS=1;
		X_Voltage_Line=11;
		X_Current_Line=10;
			ADC_Get.Voltage_Value=ADC_Voltage_Read_Value_average();
			if(ADC_Get.Voltage_Value<=6){
									//Voltage_Level_Flag
					LCD_ShowString(9,3,"6V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"0V",YELLOW,BLACK,12,0);
			}
			if(ADC_Get.Voltage_Value<=10&&ADC_Get.Voltage_Value>6){
					LCD_ShowString(9,3,"10V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"6V",YELLOW,BLACK,12,0);				
			}
			if(ADC_Get.Voltage_Value<=13&&ADC_Get.Voltage_Value>10){
					LCD_ShowString(9,3,"13V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"10V",YELLOW,BLACK,12,0);									
			}if(ADC_Get.Voltage_Value<=16&&ADC_Get.Voltage_Value>13){
					LCD_ShowString(9,3,"16V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"13V",YELLOW,BLACK,12,0);									
			}if(ADC_Get.Voltage_Value<=21&&ADC_Get.Voltage_Value>16){
					LCD_ShowString(9,3,"21V",YELLOW,BLACK,12,0);
					LCD_ShowString(9,119,"16V",YELLOW,BLACK,12,0);									
			}
			
		//LCD_ShowString(9,3,"24V",YELLOW,BLACK,12,0);
		//LCD_ShowString(9,119,"0V",YELLOW,BLACK,12,0);
		if(C_Range.Current_Range_Flag_one== 1){					
			//显示最小电压电流	
			LCD_ShowString(213-12,3,"0.5A",BLUE,BLACK,12,0);
			LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_tow== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"1A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_five== 1){					
						//显示最小电压电流	
						LCD_ShowString(213-12,3,"1.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_six== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"2A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_seven== 1){					
						//显示最小电压电流	
						LCD_ShowString(213-12,3,"2.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_eight== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"3A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_nine== 1){					
						//显示最小电压电流	
						LCD_ShowString(213-12,3,"3.5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_ten== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"4A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}		
		if(C_Range.Current_Range_Flag_three== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}
		if(C_Range.Current_Range_Flag_four== 1){					
						//显示最小电压电流	
						LCD_ShowString(213,3,"5A",BLUE,BLACK,12,0);
						LCD_ShowString(213,119,"0A",BLUE,BLACK,12,0);										
		}	
		
    if(Begin_Stop_Flag==0){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_stop);
		}else if(Begin_Stop_Flag==1){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_Begin);
		}			
	}
	
}

/*-------------------------------------------------------------
*功能：单次显示电压差曲线的电压电流量程
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Display_main_Line_Voltage(void){
	if(index_cp==9){
		menu_Ui_main_Line_Wen(BRRED);
		//显示最大电压最小电压
		ADC_GET_V_X=10;
		ADC_GET_V_Y=80;
		LCD_ShowString(120,121,"200us",GREEN,BLACK,12,0);
 		LCD_ShowString(180,3,"Ripple",GREEN,BLACK,12,0); 
		LCD_DrawRectangle(155, 17, 235, 117,GREEN);		
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
    if(Begin_Stop_Flag==0){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_stop);
		}else if(Begin_Stop_Flag==1){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_Begin);
		}
	}	
}
/*-------------------------------------------------------------
*功能：修改离线曲线的延时
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Change_Timer_Time(void){

		if(index_cp==8){
			nember_Flag++;
	    if(nember_Flag>=9){
				nember_Flag=0;
			}	
	 if(nember_Flag==0){
		 time=0;
		 Change_Time=60000;
		 Time_Change_FLAG=0;
	 }
	 if(nember_Flag==1){
		time =0;
		Change_Time=30000;	 
		 Time_Change_FLAG=1;		 
	 }
	 if(nember_Flag==2){
		time =0;
		Change_Time=10000;	 
		Time_Change_FLAG=2;		 
	 }
	 if(nember_Flag==3){
		time =0;
		Change_Time=1000;	 
		Time_Change_FLAG=3;		 
	 }
	 if(nember_Flag==4){
		time =0;
		Change_Time=500;	 
		 Time_Change_FLAG=4;		 
	 }
	 if(nember_Flag==5){
		time =0;
		Change_Time=100;	 
		Time_Change_FLAG=5;		 
	 }
	 if(nember_Flag==6){
		time =0;
		Change_Time=50;	 
		Time_Change_FLAG=6;		 
	 }
	 if(nember_Flag==7){
		time =0;
		Change_Time=20;	 
		Time_Change_FLAG=7;		 
	 }
	 if(nember_Flag==8){
		time =0;
		Change_Time=1;	 
		Time_Change_FLAG=8;		 
	 }
	 
 }	 
}

/*-------------------------------------------------------------
*功能：离线曲线的暂停
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Diaplay_Begin_Stop(u8 indexs){
	if(index_cp==indexs){

		Begin_Stop_Flag+=1;
		Delay_ms(250);
		if(Begin_Stop_Flag>=2){
			Begin_Stop_Flag =0;
		}
    if(Begin_Stop_Flag==0){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_stop);
		}else if(Begin_Stop_Flag==1){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_Begin);
		}			
	}
	if(index_cp==indexs){
    
		Begin_Stop_Ri_Flag+=1;
		Delay_ms(250);
		if(Begin_Stop_Ri_Flag>=2){
			Begin_Stop_Ri_Flag =0;
		}
    if(Begin_Stop_Ri_Flag==0){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_stop);
		}else if(Begin_Stop_Ri_Flag==1){
			LCD_Fill(161,121,175,135,BLACK);
			LCD_ShowPicture(162,122,6,12,gImage_Begin);
		}		
	}	
}


/*-------------------------------------------------------------
*功能：电流，温度保护框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Current_Temp_Ui(){
 if(index_cp==10){
		//加电流减电流UI
		LCD_Fill(186, 74, 186+44, 74+13,BLACK);	  
		LCD_DrawRectangle(11, 74,11+44,74+13,YELLOW);
		LCD_ShowString(12+4,75,"+100mA",GREEN,GREEN_NOW,12,0);
		LCD_DrawRectangle(65, 74, 65+44, 74+13,YELLOW);
		LCD_ShowString(66+4,75,"-100mA",RED_NOW,BLACK,12,0);	
		//加温度减温度UI		
		LCD_DrawRectangle(134,74,134+44,74+13,YELLOW);
		LCD_ShowString(134+12,75,"+1C",GREEN,BLACK,12,0);
		LCD_DrawRectangle(186, 74, 186+44, 74+13,YELLOW);
		LCD_ShowString(186+12,75,"-1C",RED_NOW,BLACK,12,0);			
		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
		LCD_DrawLine(120,0,120,135,GREEN);
		LCD_DrawLine(0,37,240,37,GREEN);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);  	 
 }
  if(index_cp==11){
		//加电流减电流UI
		LCD_Fill(11, 74,11+44,74+13,BLACK);
		LCD_DrawRectangle(11, 74,11+44,74+13,YELLOW);
		LCD_ShowString(12+4,75,"+100mA",GREEN,BLACK,12,0);
		LCD_DrawRectangle(65, 74, 65+44, 74+13,YELLOW);
		LCD_ShowString(66+4,75,"-100mA",RED_NOW,GREEN_NOW,12,0);	
		//加温度减温度UI		
		LCD_DrawRectangle(134,74,134+44,74+13,YELLOW);
		LCD_ShowString(134+12,75,"+1C",GREEN,BLACK,12,0);
		LCD_DrawRectangle(186, 74, 186+44, 74+13,YELLOW);
		LCD_ShowString(186+12,75,"-1C",RED_NOW,BLACK,12,0);			
		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
		LCD_DrawLine(120,0,120,135,GREEN);
		LCD_DrawLine(0,37,240,37,GREEN);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);  	 
 }
	  if(index_cp==12){
		LCD_Fill(65, 74, 65+44, 74+13,BLACK);
		//加电流减电流UI
		LCD_DrawRectangle(11, 74,11+44,74+13,YELLOW);
		LCD_ShowString(12+4,75,"+100mA",GREEN,BLACK,12,0);
		LCD_DrawRectangle(65, 74, 65+44, 74+13,YELLOW);
		LCD_ShowString(66+4,75,"-100mA",RED_NOW,BLACK,12,0);	
		//加温度减温度UI		
		LCD_DrawRectangle(134,74,134+44,74+13,YELLOW);
		LCD_ShowString(134+12,75,"+1C",GREEN,GREEN_NOW,12,0);
		LCD_DrawRectangle(186, 74, 186+44, 74+13,YELLOW);
		LCD_ShowString(186+12,75,"-1C",RED_NOW,BLACK,12,0);			
		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
		LCD_DrawLine(120,0,120,135,GREEN);
		LCD_DrawLine(0,37,240,37,GREEN);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);  	 
 }
	if(index_cp==13){
		LCD_Fill(134,74,134+44,74+13,BLACK);
		//加电流减电流UI
		LCD_DrawRectangle(11, 74,11+44,74+13,YELLOW);
		LCD_ShowString(12+4,75,"+100mA",GREEN,BLACK,12,0);
		LCD_DrawRectangle(65, 74, 65+44, 74+13,YELLOW);
		LCD_ShowString(66+4,75,"-100mA",RED_NOW,BLACK,12,0);	
		//加温度减温度UI		
		LCD_DrawRectangle(134,74,134+44,74+13,YELLOW);
		LCD_ShowString(134+12,75,"+1C",GREEN,BLACK,12,0);
		LCD_DrawRectangle(186, 74, 186+44, 74+13,YELLOW);
		LCD_ShowString(186+12,75,"-1C",RED_NOW,GREEN_NOW,12,0);			
		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
		LCD_DrawLine(120,0,120,135,GREEN);
		LCD_DrawLine(0,37,240,37,GREEN);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);  	 
 }
}
/*-------------------------------------------------------------
*功能：电流温度加减按键及进行加的算法
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Current_Temp_add(void){
	if(index_cp==10){
		C_T_P.protect_Current+=0.1;
		if(C_T_P.protect_Current>=5) C_T_P.protect_Current=5;
	}
	if(index_cp==11){
		C_T_P.protect_Current-=0.1;
		if(C_T_P.protect_Current<=0) C_T_P.protect_Current=0;
	}	
	if(index_cp==12){	
		C_T_P.protect_Temp++;		
		if(C_T_P.protect_Temp>=99)C_T_P.protect_Temp=99;
	}
	if(index_cp==13){	
		C_T_P.protect_Temp--;		
		if(C_T_P.protect_Temp<=0)C_T_P.protect_Temp=0;
	}	
}
/*-------------------------------------------------------------
*功能：电流温度设置成果显示
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
void Current_Temp_Set_succeed(void){
if(index_cp==10){
		LCD_Fill(70,40,176,92,RED_NOW);	
		LCD_ShowString(78,50,"SUCCEED",WHITE,RED_NOW,24,0);
		Delay_ms(1000);
	}
	if(index_cp==11){
		LCD_Fill(70,40,176,92,RED_NOW);	
		LCD_ShowString(78,50,"SUCCEED",WHITE,RED_NOW,24,0);	
		Delay_ms(1000);
	}	
	if(index_cp==12){	
		LCD_Fill(70,40,176,92,RED_NOW);	
		LCD_ShowString(78,50,"SUCCEED",WHITE,RED_NOW,24,0);	
		Delay_ms(1000);
	}
	if(index_cp==13){	
		LCD_Fill(70,40,176,92,RED_NOW);	
		LCD_ShowString(78,50,"SUCCEED",WHITE,RED_NOW,24,0);	
		Delay_ms(1000);
	}		
	
}


/*-------------------------------------------------------------
*功能：PD快充协议框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
static void PD_Dislay_Ui(void){
	
	if(index_cp==14){
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN);
    //2023.1.13更新		
		LCD_ShowString(105,2,"PD3.0",WHITE,BLACK,12,0);
		CH224K_PD_Voltage(OUTPUT_5V);		
    if(PD_Power_FLAG ==0){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(PD_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	  if(PD_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
    if(PD_Power_FLAG ==3){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 						
		}

		
	}
	if(index_cp==15){
		LCD_Fill(124,92,119+108,91+18,BLACK);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 
		CH224K_PD_Voltage(OUTPUT_9V);				
    //2023.1.13更新		
		LCD_ShowString(105,2,"PD3.0",WHITE,BLACK,12,0);				
    if(PD_Power_FLAG ==0){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
		if(PD_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	  if(PD_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}	
		if(PD_Power_FLAG ==3){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 						
		}

	}		
	if(index_cp==16){
		CH224K_PD_Voltage(OUTPUT_12V);		
		LCD_Fill(22,54,18+81,53+18,BLACK);		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN);
    //2023.1.13更新		
		LCD_ShowString(105,2,"PD3.0",WHITE,BLACK,12,0);				
    if(PD_Power_FLAG ==0){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(PD_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	  if(PD_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
    if(PD_Power_FLAG ==3){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 						
		}
	}			
	if(index_cp==17){
				CH224K_PD_Voltage(OUTPUT_15V);		
		LCD_Fill(128+4,54,128+87,53+18,BLACK);	
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"PD3.0",WHITE,BLACK,12,0);				
    if(PD_Power_FLAG ==0){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(PD_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	  if(PD_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
    if(PD_Power_FLAG ==3){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,BLACK,16,0); 						
		}		
	}	
	if(index_cp==18){
				CH224K_PD_Voltage(OUTPUT_20V);		
		LCD_Fill(14+4,92,14+89,91+18,BLACK);
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"PD3.0",WHITE,BLACK,12,0);				
    if(PD_Power_FLAG ==0){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,WHITE,16,0); 				
		}
    if(PD_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN_NOW);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,WHITE,16,0); 			
		}
	  if(PD_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,WHITE,16,0); 			
		}
    if(PD_Power_FLAG ==3){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"PD 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"PD 12V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(119, 91, 119+109,91+19,GREEN);
 		LCD_ShowString(123,92,"PD 20V 3.25A",YELLOW,WHITE,16,0); 						
		}
	}
}/*-------------------------------------------------------------
*功能：QC快充协议框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
static void QC_Dislay_Ui(void){
	
	if(index_cp==19){
		LCD_Fill(14, 91, 14+102,91+19,BLACK);	
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"QC2.0",WHITE,BLACK,12,0);
		LCD_DrawRectangle(130, 80, 239, 134,GREEN);		
		CH224K_PD_Voltage(OUTPUT_5V);	
		if(QC_Power_FLAG ==0){
		
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(QC_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
	  if(QC_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		//LCD_ShowString(14+4,92,"QC 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	}
	if(index_cp==20){  //QC 9V
		CH224K_PD_Voltage(OUTPUT_9V);		
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"QC2.0",WHITE,BLACK,12,0);
				LCD_DrawRectangle(130, 80, 239, 134,GREEN);
		if(QC_Power_FLAG ==0){
		
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(QC_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
	  if(QC_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,WHITE,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		//LCD_ShowString(14+4,92,"QC 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	}
	if(index_cp==21){ //QC 12V
		LCD_Fill(18, 53, 18+82,53+19,BLACK);	
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"QC2.0",WHITE,BLACK,12,0);
				LCD_DrawRectangle(130, 80, 239, 134,GREEN);
				CH224K_PD_Voltage(OUTPUT_12V);
		if(QC_Power_FLAG ==0){
		
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,WHITE,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
    if(QC_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,WHITE,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 				
		}
	  if(QC_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,WHITE,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		//LCD_ShowString(14+4,92,"QC 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,BLACK,16,0); 			
		}
	}
	if(index_cp==22){
		CH224K_PD_Voltage(OUTPUT_20V);		
		LCD_Fill(128, 53, 128+88,53+19,BLACK);	
		LCD_DrawRectangle(1, 1, 239, 134,GREEN);
 		LCD_DrawLine(0,16,240,16,GREEN);   		
 		LCD_DrawLine(120,16,120,16+22,GREEN);
 		LCD_DrawLine(0,37,240,37,GREEN); 	
		LCD_ShowString(105,2,"QC2.0",WHITE,BLACK,12,0);
				LCD_DrawRectangle(130, 80, 239, 134,GREEN);
		if(QC_Power_FLAG ==0){
		
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN_NOW);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,WHITE,16,0); 				
		}
    if(QC_Power_FLAG ==1){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN_NOW);
 		//LCD_ShowString(14+4,92,"PD 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,WHITE,16,0); 				
		}
	  if(QC_Power_FLAG ==2){
		LCD_DrawRectangle(18, 53, 18+82,53+19,GREEN);
 		LCD_ShowString(22,54,"QC 9V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(128, 53, 128+88,53+19,GREEN_NOW); 
 		LCD_ShowString(128+4,54,"QC 12V 3A",YELLOW,BLACK,16,0);
		//LCD_DrawRectangle(14, 91, 14+90,91+19,GREEN);
 		//LCD_ShowString(14+4,92,"QC 15V 3A",YELLOW,BLACK,16,0);
		LCD_DrawRectangle(14, 91, 14+102,91+19,GREEN_NOW);
 		LCD_ShowString(14+4,92,"QC 20V 3.25A",YELLOW,WHITE,16,0); 			
		}
	}	
}
/*-------------------------------------------------------------
*功能：5V输出设置框图
*作者：小夏
*修改时间：2023.2.24
*参考：（大脑）自己
*-------------------------------------------------------------*/
static void Voltage_OUTPUT_5V_Succeed(void){
	if(index_cp==7){
		CH224K_PD_Voltage(OUTPUT_5V);
		LCD_ShowString(78,50,"SUCCEED",WHITE,RED_NOW,24,0);	
		Delay_ms(1000);		
	}
}