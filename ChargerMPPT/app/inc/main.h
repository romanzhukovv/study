#include "stm32f334x8.h"
#include "FreeRTOS.h"
#include "task.h"

void vTask1(void *argument);
void vTask2(void *argument);

void InitSystemClockMCU();
