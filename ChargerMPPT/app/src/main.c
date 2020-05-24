#include "main.h"

int main (void)
{
	InitSystemClockMCU();

	xTaskCreate(vTask1, "LedBlue", 256, NULL, 1, NULL);
	xTaskCreate(vTask2, "ADC", 256, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1)
	{

	}
}

void vTask1(void *argument)
{

}

void vTask2(void *argument)
{

}
