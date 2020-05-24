#include "SysInit.h"

void InitSystemClockMCU (void) {

    RCC->CR |= RCC_CR_HSEON;                                    // Enable system for external crystall
	while (!(RCC->CR & RCC_CR_HSERDY));                         // Waiting flag about enable

    FLASH->ACR |= FLASH_ACR_LATENCY_1;                          // Latency for internal flash memory

    RCC->CFGR  |= RCC_CFGR_PLLMUL9;                             // Select multiplier frequency for PLL

    RCC->CFGR  |= RCC_CFGR_PLLSRC;                              // Select source external crystall
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV1;                     // Select divider for ADC = AHB/1

    RCC->CR |= RCC_CR_PLLON;                                    // Enable PLL system
	while((RCC->CR & RCC_CR_PLLRDY) == 0){}                     // Waiting flag about enable

    RCC->CFGR |= RCC_CFGR_SW_PLL;                               // Select source SYSCLK = PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}      // Waiting flag about enable
}
