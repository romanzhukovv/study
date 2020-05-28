/***************************Library*******************************/

#include "sysInit.h"

/*************************Functions*******************************/

void RCC_Init(void)
{
	
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);									//HSE Enable
	while(!(RCC->CR & RCC_CR_HSERDY));										//HSE is ready				
	
	FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;						//Tact for Flash
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;										//AHB = SYSCLK/1 = 48
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;										//APB1 = HCLK/2 = 24
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;										//APB2 = HCLK/1 = 48

	RCC->CFGR2 |= RCC_CFGR2_PREDIV1SRC_HSE;									//Prediv1 Source - HSE
	RCC->CFGR2 |= RCC_CFGR2_PREDIV1_DIV1;									//Previv1 = HSE/1 = 8
	RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;										//PLL source - Prediv1
	RCC->CFGR |= RCC_CFGR_PLLMULL6;											//PLLCLK = Prediv1 * 6 = 48
	
	RCC->CR |= RCC_CR_PLLON;												//PLL Enable
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}									//PLL is ready
	
	RCC->CFGR &= ~RCC_CFGR_SW;												//Clear SW bits
	RCC->CFGR |=RCC_CFGR_SW_PLL;											//Select sourse SYSCLK - PLLCLK
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}					//Wait till PLL is used
	
}

void GPIO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 									//Takt on for port C
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 									//Takt on for port A
	
	//GPIOC->CRH &= ~GPIO_CRH_CNF9; 	  									//PC9 in output
	//GPIOC->CRH |= GPIO_CRH_MODE9_0; 										//PC9 in output, speed 10 MHz
	
	//GPIOA->CRH &= ~GPIO_CRH_CNF9; 	 	 								//PA9 in output
	//GPIOA->CRH |= GPIO_CRH_MODE9_0; 										//PA9 in output, speed 10 MHz
	
	GPIOC->CRH &= ~GPIO_CRH_CNF11; 											//PC11 in output
	GPIOC->CRH |= GPIO_CRH_MODE11_0; 										//PC11 in output, speed 10 MHz
	GPIOC->BSRR |= GPIO_BSRR_BR11; 											//Reset PC11
	
	//GPIOC->CRH &= ~GPIO_CRH_CNF12; 										//PC12 in output
	//GPIOC->CRH |= GPIO_CRH_MODE12_0; 										//PC12 in output, speed 10 MHz
	
	//GPIOC->BSRR |= GPIO_BSRR_BR9; 										//Reset PC9
	//GPIOA->BSRR |= GPIO_BSRR_BR9;											//Reset PA9

	GPIOA->CRL &= ~GPIO_CRL_CNF4_1;											//Input floating mode PA4
	GPIOA->CRL |= GPIO_CRL_CNF4_0;											//Input floating mode PA4
	GPIOA->CRL &= ~GPIO_CRL_MODE4;											//Input floating mode PA4
}

void MCO_out(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= GPIO_CRH_MODE8;
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
	
}