#ifndef __usart2_H
#define __usart2_H
#include <STC32G.H>
#include "stdio.h"
#include "uart1.h"
#define Fosc     35000000L  //定义主时钟
#define Baudrate2      115200L
#define TM3            (65536 -(Fosc/Baudrate2/4))
void Uart2_Init(void);
void Uart2_Putc(unsigned char dat);
char putchar(char c);

#endif
