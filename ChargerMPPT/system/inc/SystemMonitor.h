/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        SystemMonitor.h                                                  *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        14.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       System monitoring and output debug information                   *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/
#pragma once 

#include "stm32f3xx.h"

#include "DebugOutput.h"
#include "Delay.h"

/********************************************************************************
 * External variable
 ********************************************************************************/

extern float resultCurrentOutput;
extern float resultVoltageOutput;
extern float resultCurrentInput;
extern float resultVoltageInput;

/********************************************************************************
 * Local function declaration
 ********************************************************************************/

void StartSystemMonitoring (void);
void InitTimerForDebug (uint16_t milliseconds);

/********************************* END OF FILE **********************************/