/***************************Library*******************************/

#include "stm32f1xx.h"
#include "cmsis_os.h"
#include "sysInit.h"
#include "uartLib.h"
#include "pwmLib.h"

/***************************Defines*******************************/

xQueueHandle SendData;

/************************Tasks FreeRTOS***************************/

void vTaskSendValue(void *argument);
void vTaskConvertADC(void *argument);