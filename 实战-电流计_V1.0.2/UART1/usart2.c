#include "usart2.h"



void Uart2_Init(void)
{
	S2_S = 1;       //UART2 switch to: 0: P1.0 P1.1,  1: P4.6 P4.7
	S2CON = 0x40; 
	
	S2REN =1;
	S2CFG = 0x01;
	T2L  = TM3;
	T2H  = TM3>>8;
	AUXR |= 0x14;	//定时器2时钟1T模式,开始计时
}
void Uart2_Putc(unsigned char dat)
{
	S2BUF  = dat; 
	while(S2TI == 0);
	S2TI = 0;    //Clear Tx flag
}

/*
char putchar(char c)
{
	Uart2_Putc(c);
	return c;
}
*/