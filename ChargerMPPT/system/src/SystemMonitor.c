/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        SystemMonitor.c                                                  *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        14.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       System monitoring and output debug information                   *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "SystemMonitor.h"

/********************************************************************************
 * Initialization and start system monitoring
 ********************************************************************************/

void StartSystemMonitoring (void) {

    InitSysTick();
    InitUSARTforDebug();
    InitTimerForDebug(3000);
}

/********************************************************************************
 * Initialization timer (TIM6) for output debug information
 * Prescaler for 0.5 ms: 72 000 000 / 36 000 = 2000 Hz
 * Set period
 ********************************************************************************/

void InitTimerForDebug (uint16_t milliseconds) {

    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;     // Clock enable TIM6

	TIM6->PSC = 36000-1;					// Prescaler for 0.5 ms
	TIM6->ARR = milliseconds*2-1;			// Period

	TIM6->DIER |= TIM_DIER_UIE;				// Enable interrupt
	TIM6->CR1  |= TIM_CR1_CEN;				// Enable counter

	NVIC_EnableIRQ(TIM6_DAC1_IRQn);			// Enable interrupt for handler TIM2
}    

/********************************************************************************
 * Handler for TIM6 and output information
 ********************************************************************************/

void TIM6_DAC1_IRQHandler (void) {

	TIM6->SR &= ~TIM_SR_UIF;
    
    printf (" \n");
	printf ("New data feedback:\n");

    printf ("Iout = %.2fA\n", resultCurrentOutput);
    printf ("Vout = %.2fV\n", resultVoltageOutput);
    printf ("Iin = %.2fA\n",  resultCurrentInput);
    printf ("Vin = %.2fV\n",  resultVoltageInput);
}

/********************************* END OF FILE **********************************/