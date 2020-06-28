/***************************Library*******************************/

#include "main.h"

/*****************************Main*******************************/

int main(void)
{
    RCC_Init();
    GPIO_Init();
	dacInit();
	
	xTaskCreate(vTaskOutDAC, "DAC", 32, NULL, 1, NULL);
	
	vTaskStartScheduler();

    while (1)
    {

    }
  
}

/*****************************Tasks*******************************/

void vTaskOutDAC(void *argument)
{
	uint16_t i = 0;
	while(1)
	{
		writeDAC(i);
		i++;
		if (i==4095)
		{
			i = 0;
		}
		vTaskDelay(10);
	}
}

/*****************************Interupts*******************************/
