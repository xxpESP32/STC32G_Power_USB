#include "Spi_Handler.h"

void SPI_Init(void){
	//CS=1;
	P10=1;
//	SPI_S1 = 0;
//  SPI_S0 = 0;
  P_SW1=0x00;
	SPDAT=0;
	SPCTL =0x50;
	SPSTAT=0xc0;
	
}
