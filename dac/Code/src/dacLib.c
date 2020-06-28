/***************************Library*******************************/

#include "dacLib.h"

/*************************Functions*******************************/

//PA5 - TP7 - DAC2

void dacInit(void){
	
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL &= ~GPIO_CRL_MODE5;
	
	DAC->CR |= DAC_CR_EN2;
	
}

void writeDAC(uint16_t data){
	
	if (data < 4096){DAC->DHR12R2 = data;}
	
}