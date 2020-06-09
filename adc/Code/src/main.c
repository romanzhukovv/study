/***************************Library*******************************/

#include "main.h"

/*****************************Main*******************************/

int main(void)
{
    RCC_Init();
    GPIO_Init();
	USART3_Init();
	//adcInit();

	xTaskCreate(vTaskSendValue, "Value", 32, NULL, 1, NULL);
	xTaskCreate(vTaskConvertADC, "ADC", 32, NULL, 1, NULL);

	SendData = xQueueCreate(5, sizeof(uint8_t));
	
	vTaskStartScheduler();

    while (1)
    {

    }
  
}

/*****************************Tasks*******************************/

void vTaskSendValue(void *argument)
{
	uint8_t data;

	while (1)
	{
		if (uxQueueMessagesWaiting(SendData) != 0){
			
			xQueueReceive(SendData, &data, 0);
			SendDataUSART3(data);
			
		}
		
		vTaskDelay(100);
	}
}

void vTaskConvertADC(void *argument)
{
	uint8_t i = 0;
	
	while(1)
	{
		i++;
		xQueueSend(SendData, &i, 0);
		vTaskDelay(1000);
	}
}

/*****************************Interupts*******************************/
