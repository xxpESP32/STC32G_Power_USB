#ifndef __uart1_H
#define __uart1_H
#include <STC32G.H>
#include "stdio.h"
#include "usart2.h"

#define MAIN_Fosc     35000000L  //定义主时钟
#define Baudrate      115200L
#define TM            (65536 -(MAIN_Fosc/Baudrate/4))

extern char buff[64];
extern char rx_len;

void Uart1_Init(void);
void Usart1_Send(unsigned char dat);
void Usart1_Send_Str(char* dat);
#endif