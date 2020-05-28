/***************************Library*******************************/

#include "main.h"

/*****************************Main*******************************/

int main(void)
{
    RCC_Init();
    GPIO_Init();
	//USART3_Init();
	PWM_Init();
	//MCO_out();

	//xTaskCreate(vTaskLed1, "LED1", 32, NULL, 2, NULL);
	//xTaskCreate(vTaskLed2, "LED2", 32, NULL, 1, NULL);
	xTaskCreate(vTaskButtonUser, "LED1", 32, NULL, 1, NULL);
	
	vTaskStartScheduler();

    while (1)
    {

    }
  
}

/*****************************Tasks*******************************/

void vTaskLed1(void *argument)
{
	while (1)
	{
		GPIOC->BSRR |= GPIO_BSRR_BR11; 		//Reset PC11
		vTaskDelay(1000);
		GPIOC->BSRR |= GPIO_BSRR_BS11; 		//Set PC11
		vTaskDelay(1000);
	}
}

void vTaskLed2(void *argument)
{
	while (1)
	{
		GPIOC->BSRR |= GPIO_BSRR_BS12; 		//Reset PC12
		vTaskDelay(1000);
		GPIOC->BSRR |= GPIO_BSRR_BR12; 		//Set PC12
		vTaskDelay(1000);
	}
}

void vTaskButtonUser(void *argument)
{
	while (1)
	{	
		for(uint16_t i=0; i<=1000; i++)
		{	
			TIM1->CCR2 = i;
			vTaskDelay(1);
		}	
		for(int16_t j=1000; j>=0; j--)
		{
			TIM1->CCR2 = j;
			vTaskDelay(1);
		}
	}
}

/*****************************Interupts*******************************/

void USART3_IRQHandler(void)
{
	if (USART3->SR & USART_SR_RXNE)
	{
		USART3->SR &= ~USART_SR_RXNE;
		
		if (USART3->DR == '0')
		{
			USART3_Send_String("OFF\r\n");
			GPIOC->BSRR |= GPIO_BSRR_BR12; 		//Set PC12
		}
		
		if (USART3->DR == '1')
		{
			USART3_Send_String("ON\r\n");
			GPIOC->BSRR |= GPIO_BSRR_BS12; 		//Reset PC12
		}
	}
	
}