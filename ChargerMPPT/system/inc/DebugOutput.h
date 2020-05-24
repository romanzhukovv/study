/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        DebugOutput.h                                                    *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        01.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Output debug information in the terminal                         *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/
#pragma once 

#include <stdio.h>

#include "stm32f3xx.h"

#include "USART.h"

/********************************************************************************
 * Local function declaration
 ********************************************************************************/

int uart_putc (const char ch);

/********************************* END OF FILE **********************************/