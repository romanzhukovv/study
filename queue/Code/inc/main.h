/***************************Library*******************************/

#include "stm32f1xx.h"
#include "cmsis_os.h"
#include "sysInit.h"
#include "uartLib.h"
#include "pwmLib.h"

/***************************Defines*******************************/

xQueueHandle SendData;

/************************Tasks FreeRTOS***************************/

void vTaskLed1(void *argument);
void vTaskLed2(void *argument);
void vTaskButtonUser(void *argument);