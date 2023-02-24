#include "uart1.h"
char buff[64];
char rx_len;
void Uart1_Init(void){
	S1_S1=0;
	S1_S0=0; //使用P3.0，P3.1
	SCON=0x40;
	REN=1;
	S1BRT =1;
	T2L  = TM;
	T2H  = TM>>8;
	AUXR |= 0x14;	//定时器2时钟1T模式,开始计时
	rx_len=0;
	
	ES=1;
	EA=1;
	
}
void Usart1_Send(unsigned char dat)
{
	SBUF=dat;
	while(TI==0);
	TI=0;
}
char putchar(char c)
{
	Usart1_Send(c);
	return c;
}

void Usart1_Send_Str(char* dat)
{
	while(*dat){
	Usart1_Send(*dat++);
	}
}

void USART_BackCall_IRQ(void) interrupt 4
{
	
		if(RI){
			RI=0;
			if(SBUF=='\n'){
				buff[rx_len++]='\0';
				rx_len =0;
			}else{
				buff[rx_len++]=SBUF;
				P20=!P20;
			}
			
		}
	
} 