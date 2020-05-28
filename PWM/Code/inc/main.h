/***************************Library*******************************/

#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "sysInit.h"
#include "uartLib.h"
#include "pwmLib.h"

/***************************Defines*******************************/

/************************Tasks FreeRTOS***************************/

void vTaskLed1(void *argument);
void vTaskLed2(void *argument);
void vTaskButtonUser(void *argument);