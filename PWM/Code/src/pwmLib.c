/***************************Library*******************************/

#include "pwmLib.h"

/*************************Functions*******************************/

void PWM_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 									//Takt on for port A
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;										//Takt on Alternate function IO
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;										//TIM1 Enable

	GPIOA->CRH &= ~GPIO_CRH_CNF9_0; 	 	 								//PA9 in Alternate output
	GPIOA->CRH |= GPIO_CRH_CNF9_1;						 	 	 			//PA9 in Alternate output
	GPIOA->CRH |= GPIO_CRH_MODE9; 											//PA9 in output, speed 50 MHz

	TIM1->PSC = 48-1;														//Предделитель для TIM1
	TIM1->ARR = 1000;														//Период ШИМ
	TIM1->CCR2 = 500;														//Заполнение ШИМ
	
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;	//Polarity of PWM
	TIM1->CCER |= TIM_CCER_CC2E;											//Generating PWM
	TIM1->CCER |= TIM_CCER_CC2P;											//Active level

	TIM1->BDTR |= TIM_BDTR_MOE;
	
	TIM1->CR1 &= ~TIM_CR1_DIR;												//Direction
	TIM1->CR1 |= TIM_CR1_CEN;												//Generating PWM
}