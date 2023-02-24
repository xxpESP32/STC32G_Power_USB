#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "STC32G.H"
#include "system.h"

#define SOFTWARE 1

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif


#define LCD_SCL P15//SCLK
#define LCD_SDA P13//MOSI
#define LCD_RES P14//RES
#define LCD_DC  P11//DC
//#define LCD_BLK P24 //BLK
#define LCD_CS  P10 //CS1

//-----------------LCD�˿ڶ���----------------

#define LCD_SCLK_Clr() LCD_SCL=0//SCL=SCLK
#define LCD_SCLK_Set() LCD_SCL=1

#define LCD_MOSI_Clr() LCD_SDA=0//SDA=MOSI
#define LCD_MOSI_Set() LCD_SDA=1

#define LCD_RES_Clr() LCD_RES=0//RES
#define LCD_RES_Set() LCD_RES=1

#define LCD_DC_Clr() LCD_DC=0//DC
#define LCD_DC_Set() LCD_DC=1

//#define LCD_BLK_Clr()  LCD_BLK=0//BLK
//#define LCD_BLK_Set()  LCD_BLK=1

#define LCD_CS_Clr()  LCD_CS=0//CS1
#define LCD_CS_Set()  LCD_CS=1



void delay_ms(unsigned int ms);//��׼ȷ��ʱ����
void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(unsigned char dat);//ģ��SPIʱ��
void LCD_WR_DATA8(unsigned char dat);//д��һ���ֽ�
void LCD_WR_DATA(unsigned short dat);//д�������ֽ�
void LCD_WR_REG(unsigned char dat);//д��һ��ָ��
void LCD_Address_Set(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




