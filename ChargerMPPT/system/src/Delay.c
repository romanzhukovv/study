/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        VoltageAndCurrentAdc.h                                           *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        09.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Adding function delay for SysTick timer                          *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Delay.h"

/********************************************************************************
 * Used variable
 ********************************************************************************/

volatile uint32_t delayCounter = 0;

/********************************************************************************
 * Initialization for SysTick timer
 ********************************************************************************/

void InitSysTick (void) {

	SysTick->LOAD = 72000000UL/1000 - 1; 		// Set 1 tick = 1 ms
	SysTick->VAL = 72000000UL/1000 - 1; 		// Set value

	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk  | SysTick_CTRL_ENABLE_Msk;
}

/********************************************************************************
 * Hardware function delay
 ********************************************************************************/

void Delay (uint32_t milliseconds) {

	delayCounter = milliseconds;
	while (delayCounter != 0);
}

/********************************************************************************
 * Handler for SysTick timer's interrupt
 ********************************************************************************/

void SysTick_Handler (void) {

	delayCounter--;
}
