#include "Pwm.h"
void Pwm_Init_D_L(void){
		PWMB_PS=0x08; //08 PWM6_3通道 0A PWM6_3通道& PWM5_3通道
	//PWMB_PS=0x08;
	
	PWMB_CCER1=0x00;
	
	PWMB_CCMR2=0x60; //PWM6
	//PWMB_CCMR1=0x60; //PWM5
	
	PWMB_CCER1=0x10;//PWM6
	//PWMB_CCER1=0x01;//PWM5
	//PWM6 D+
	PWMB_CCR6H=0x30;
	PWMB_CCR6L=0x0F;	
	//PWM5 D-
	//PWMB_CCR5H=0x30;
	//PWMB_CCR5L=0xFF;	
	
	
	PWMB_ARRH=0xFF;
	PWMB_ARRL=0x00;
	//PWM6
	PWMB_ENO=0x04;
	//PWM5
	//PWMB_ENO=0x01;
	
	PWMB_BKR=0x80;
	PWMB_CR1=0x01;
}
void Pwm_Init_D_H(void){
		PWMB_PS=0x02; //08 PWM6_3通道 0A PWM6_3通道& PWM5_3通道
	//PWMB_PS=0x08;
	
	PWMB_CCER1=0x00;
	
	//PWMB_CCMR2=0x60; //PWM6
	PWMB_CCMR1=0x60; //PWM5
	
	//PWMB_CCER1=0x10;//PWM6
	PWMB_CCER1=0x01;//PWM5
	//PWM6 D+
	PWMB_CCR5H=0x30;
	PWMB_CCR5L=0xFF;	
	//PWM5 D-
	//PWMB_CCR5H=0x30;
	//PWMB_CCR5L=0xFF;	
	
	
	PWMB_ARRH=0xFF;
	PWMB_ARRL=0x00;
	//PWM5
	PWMB_ENO=0x01;
	//PWM5
	//PWMB_ENO=0x01;
	
	PWMB_BKR=0x80;
	PWMB_CR1=0x01;
}
void Pwm_Init(void){
	PWMB_PS=0x0A; //08 PWM6_3通道 0A PWM6_3通道& PWM5_3通道
	//PWMB_PS=0x08;
	
	PWMB_CCER1=0x00;
	
	PWMB_CCMR2=0x00; //PWM6
	PWMB_CCMR1=0x00; //PWM5
	
	PWMB_CCER1=0x00;//PWM6
	//PWMB_CCER1=0x01;//PWM5
	//PWM6 D+
	PWMB_CCR6H=0x00;
	PWMB_CCR6L=0x00;	
	//PWM5 D-
	//PWMB_CCR5H=0x30;
	//PWMB_CCR5L=0xFF;	
	PWMB_CCR5H=0x00;
	PWMB_CCR5L=0x00;		
	
	PWMB_ARRH=0x00;
	PWMB_ARRL=0x00;
	//PWM6
	PWMB_ENO=0x00;
	//PWM5
	//PWMB_ENO=0x01;
	
	PWMB_BKR=0x00;
	PWMB_CR1=0x00;
}
void Pwm_Init_2(void){
	PWMB_PS=0x0A; //08 PWM6_3通道 0A PWM6_3通道& PWM5_3通道
	//PWMB_PS=0x08;
	
	PWMB_CCER1=0x00;
	
	PWMB_CCMR2=0x60; //PWM6
	PWMB_CCMR1=0x60; //PWM5
	
	PWMB_CCER1=0x11;//PWM6
	//PWMB_CCER1=0x01;//PWM5
	//PWM6 D+
	PWMB_CCR6H=0xFF;
	PWMB_CCR6L=0x00;	
	//PWM5 D-
	PWMB_CCR5H=0x30;
	PWMB_CCR5L=0x00;	
	//PWMB_CCR5H=0x00;
	//PWMB_CCR5L=0x00;		
	
	PWMB_ARRH=0xFF;
	PWMB_ARRL=0x00;
	//PWM6
	PWMB_ENO=0x05;
	//PWM5
	//PWMB_ENO=0x01;
	
	PWMB_BKR=0x80;
	PWMB_CR1=0x01;
}