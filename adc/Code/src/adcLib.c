/***************************Library*******************************/

#include "adcLib.h"

/*************************Functions*******************************/

void adcInit(void)
{
	//PA0 - net ADC5

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   	//Takt Port A
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	  	//Alt function EN

	GPIOA->CRL &= ~GPIO_CRL_CNF0;			//Analog Input
	GPIOA->CRL &= ~GPIO_CRL_MODE0;			//Analog Input

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		//ADC1 EN
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV4;		//Prescaler ADC /4

	ADC1->CR2 |= ADC_CR2_CAL; 				//Start calibration
	while (!(ADC1->CR2 & ADC_CR2_CAL));		//Waiting for calibration

	ADC1->CR2 |= ADC_CR2_ADON;     			// enable ADC
	ADC1->CR2 &= ~ADC_CR2_CONT;				// 0 - single conversion, 1 - continuous conversion	
	ADC1->CR2 |= ADC_CR2_EXTSEL;      		// event start conversion SWSTART
	ADC1->CR2 |= ADC_CR2_EXTTRIG;           // enable start conversion external signal
	ADC1->SMPR1 |= ADC_SMPR1_SMP16; 		// sempling 239.5 cycle
	ADC1->SQR3 &= ~ADC_SQR3_SQ1;    		// selection channel


}

uint16_t adcConvert (void)
{
	ADC1->CR2 |= ADC_CR2_SWSTART;
		
	while (!(ADC1->SR & ADC_SR_EOC));
	return (ADC1->DR);
}
