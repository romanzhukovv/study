/***************************Library*******************************/

#include "stm32f1xx.h"
#include "cmsis_os.h"
#include "sysInit.h"
#include "uartLib.h"
#include "adcLib.h"

/***************************Defines*******************************/

xQueueHandle SendDataADC;

/************************Tasks FreeRTOS***************************/

void vTaskSendValue(void *argument);
void vTaskConvertADC(void *argument);