/***************************Library*******************************/

#include "main.h"

/*****************************Main*******************************/

int main(void)
{
    RCC_Init();
    GPIO_Init();
	USART3_Init();
	adcInit();

	xTaskCreate(vTaskSendValue, "Value", 128, NULL, 1, NULL);
	xTaskCreate(vTaskConvertADC, "ADC", 128, NULL, 1, NULL);

	SendDataADC = xQueueCreate(5, sizeof(uint16_t));
	
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
		if (uxQueueMessagesWaiting(SendDataADC) != 0){
			
			xQueueReceive(SendDataADC, &data, 0);
			SendDataUSART3(data);
			
		}
		
		vTaskDelay(100);
	}
}

void vTaskConvertADC(void *argument)
{
	uint16_t adcResult = 0;
	
	while(1)
	{
		adcResult = adcConvet ();
		xQueueSend(SendDataADC, &adcResult, 0);
		vTaskDelay(200);
	}
}

/*****************************Interupts*******************************/
