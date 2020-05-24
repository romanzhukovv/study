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
#pragma once 

#include "stm32f3xx.h"

/********************************************************************************
 * Local function declaration
 ********************************************************************************/

void InitSysTick (void);
void Delay (uint32_t milliseconds);

/********************************* END OF FILE **********************************/