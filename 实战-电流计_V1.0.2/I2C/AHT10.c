/*
*注意：使用keil需要设置为GB2312
*==============================AHT10温湿度传感器源文件=======================
*-------------------------------------------------------------------
*文件修改历史
*<时间>    | <版本>  | <作者>  | <功能>  
*2023.2.24 | V1.0.2   | 小夏    | AHT10温湿度传感器配置
*-------------------------------------------------------------------
*如需要教学请到CSDN上面搜索"单片有机机"的STC32G专栏
*/

#include "AHT10.h"


#define AHT_ADDRESS 0X70 //0X38从机地址
#define AHT_WRITE   0X70	//0X38写地址
#define AHT_READ    0X71 //0X39读地址

u8 ACK,DATA[6];
u8 IN=0;
/*-------------------------------------------------------------
*功能：AHT10初始化配置
*作者：小夏
*修改时间：2023.2.24
*参考：<AHT10技术手册>
*-------------------------------------------------------------*/
u8 AHT10_State(void){        //����0 ������ 1
	
	u8 ACK;
	I2C_Init(I2C_GPIO_2);
	//I2C_Start();
	//I2C_Write_Byte(AHT_WRITE);
	//ACK = I2C_Write_Ack();
	//I2C_Stop();
	
	return ACK;
}
/*-------------------------------------------------------------
*功能：AHT10写配置
*作者：小夏
*修改时间：2023.2.24
*参考：<AHT10技术手册>
*-------------------------------------------------------------*/
void AHT10_Write_Init(void){ //	bit3 0 1
	
	I2C_Start();
	I2C_Send_Byte(AHT_WRITE);
	I2C_Wait_ACK();
	I2C_Send_Byte(0XE1);
	I2C_Wait_ACK();
	I2C_Send_Byte(0X08);
	I2C_Wait_ACK();
	I2C_Send_Byte(0X00);
	I2C_Wait_ACK();
	I2C_Stop();
	Delay_ms(40);
}
/*-------------------------------------------------------------
*功能：AHT10读配置
*作者：小夏
*修改时间：2023.2.24
*参考：<AHT10技术手册>
*-------------------------------------------------------------*/
void AHT10_Write_Reset(void){
	
	I2C_Start();
	I2C_Send_Byte(AHT_WRITE);
		I2C_Wait_ACK();
	I2C_Send_Byte(0XBA);
		I2C_Wait_ACK();
	I2C_Stop();
	Delay_ms(40);
}
/*-------------------------------------------------------------
*功能：AHT10读取温湿度配置
*作者：小夏
*修改时间：2023.2.24
*参考：<AHT10技术手册>
*-------------------------------------------------------------*/
u8 AHT10_Read_Humi_Temp( unsigned int *HUMI,  unsigned int *TEMP){ // 0�������� 1 ���ݴ���
	u32 humi = 0;
	u32 temp = 0;
  unsigned long return_value;
	
	I2C_Start();
	I2C_Send_Byte(AHT_WRITE);
	I2C_Wait_ACK();
	I2C_Send_Byte(0XAC);
	I2C_Wait_ACK();
	I2C_Send_Byte(0X33);
	I2C_Wait_ACK();
	I2C_Send_Byte(0X00);
	I2C_Wait_ACK();
	I2C_Stop();
	Delay_ms(80);
	
	I2C_Start();
	I2C_Send_Byte(AHT_READ);
	I2C_Wait_ACK();
	ACK = I2C_Read_Byte();
	I2C_ACK();
	//I2C_Sende_Ack(0); 		//0000 1000 BIT3 0
	//I2C_ACK();
	//I2C_Delay();

	if((ACK&0X08) == 0){
		
		AHT10_Write_Init();
	}
	if((ACK&0X80) == 0){ 	//bit7 1 0
		
		for(IN=0;IN<5;IN++){ // 0 1 2 3 4 5 ++i
			
			DATA[IN] = I2C_Read_Byte();
			
			if(IN == 4)
				
				I2C_NACK();
			else
				I2C_ACK();
		}
		I2C_Stop();
		//humi =humi+DATA[0];
		//humi=(humi<<8)+DATA[1];
		//humi=((humi<<8)+DATA[2])>>4;
	/*	humi = (DATA[0]<<12)|(DATA[1]<<4)|(DATA[2]>>4);
		temp = ((DATA[2]&0X0F)<<16)|(DATA[3]<<8)|(DATA[4]);
		printf("HUMI_data=%d\nsize=%d\n",humi,1);
		printf("TEMP_data=%d\n",temp);
		
		*HUMI = (humi * 1000/1024/1024);
		*TEMP = (temp * 2000/1024/1024+0.5)/10-50;
	*/
		return_value =0;
		return_value=(DATA[0]<<8)|DATA[1];
		return_value=((return_value<<8)|DATA[2])>>4;
		return_value=return_value & 0x000fffff;
		*HUMI =(return_value*1000/1024/1024);
		
		return_value =0;
		return_value =((DATA[2]% 16)<<8)|DATA[3];
		return_value =(return_value<<8)|DATA[4];
		return_value =return_value &0x000fffff;
		*TEMP =(return_value*200*10/1024/1024-500);
		return 0;
	}
	
	return 1;
}