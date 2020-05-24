/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        DebugOutput.c                                                    *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        01.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Output debug information in the terminal                         *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "DebugOutput.h"

/********************************************************************************
 * Output symbol for standart printf
 ********************************************************************************/

int uart_putc (const char ch) {

    SendSymbolForUSART (ch);
    return ch;
}