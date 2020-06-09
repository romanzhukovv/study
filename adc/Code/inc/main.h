/***************************Library*******************************/

#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "sysInit.h"
#include "uartLib.h"
#include "adcLib.h"

/***************************Defines*******************************/

QueueHandle_t SendDataADC;

/************************Tasks FreeRTOS***************************/

void vTaskSendValue(void *argument);
void vTaskConvertADC(void *argument);