#include "main.h"

void RCC_Init(void);
void GPIO_Init(void);
void USART3_Init(void);
void USART3_Send(char chr);
void USART3_Send_String(char* str);
//void USART3_IRQHandler(void);
//void MCO_out(void);


//void vTaskLed1(void *argument);
//void vTaskLed2(void *argument);
void vTaskButtonUser(void *argument);

int main(void)
{
    RCC_Init();
    GPIO_Init();
	USART3_Init();
	//USART3_IRQHandler();
	//MCO_out();

	//xTaskCreate(vTaskLed1, "LED1", 32, NULL, 2, NULL);
	//xTaskCreate(vTaskLed2, "LED2", 32, NULL, 1, NULL);
	xTaskCreate(vTaskButtonUser, "LED1", 32, NULL, 1, NULL);
	
	vTaskStartScheduler();

    while (1)
    {
    
    }
  
}

//----------------------------------------------------------------------------------------------------

void RCC_Init(void)
{
	
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);									//HSE Enable
	while(!(RCC->CR & RCC_CR_HSERDY));										//HSE is ready				
	
	FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;						//Tact for Flash
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;										//AHB = SYSCLK/1 = 48
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;										//APB1 = HCLK/2 = 24
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;										//APB2 = HCLK/1 = 48

	RCC->CFGR2 |= RCC_CFGR2_PREDIV1SRC_HSE;									//Prediv1 Source - HSE
	RCC->CFGR2 |= RCC_CFGR2_PREDIV1_DIV1;									//Previv1 = HSE/1 = 8
	RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;										//PLL source - Prediv1
	RCC->CFGR |= RCC_CFGR_PLLMULL6;											//PLLCLK = Prediv1 * 6 = 48
	
	RCC->CR |= RCC_CR_PLLON;												//PLL Enable
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}									//PLL is ready
	
	RCC->CFGR &= ~RCC_CFGR_SW;												//Clear SW bits
	RCC->CFGR |=RCC_CFGR_SW_PLL;											//Select sourse SYSCLK - PLLCLK
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}					//Wait till PLL is used
	
}

void GPIO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; 									//Takt on for port C
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 									//Takt on for port A
	
	GPIOC->CRH &= ~GPIO_CRH_CNF9; 	  										//PC9 in output
	GPIOC->CRH |= GPIO_CRH_MODE9_0; 										//PC9 in output, speed 10 MHz
	
	//GPIOA->CRH &= ~GPIO_CRH_CNF9; 	 	 								//PA9 in output
	//GPIOA->CRH |= GPIO_CRH_MODE9_0; 										//PA9 in output, speed 10 MHz
	
	//GPIOC->CRH &= ~GPIO_CRH_CNF11; 										//PC11 in output
	//GPIOC->CRH |= GPIO_CRH_MODE11_0; 										//PC11 in output, speed 10 MHz
	
	GPIOC->CRH &= ~GPIO_CRH_CNF12; 											//PC12 in output
	GPIOC->CRH |= GPIO_CRH_MODE12_0; 										//PC12 in output, speed 10 MHz
	
	GPIOC->BSRR |= GPIO_BSRR_BR9; 											//Reset PC9
	//GPIOA->BSRR |= GPIO_BSRR_BR9;											//Reset PA9

	GPIOA->CRL &= ~GPIO_CRL_CNF4_1;											//Input floating mode PA4
	GPIOA->CRL |= GPIO_CRL_CNF4_0;											//Input floating mode PA4
	GPIOA->CRL &= ~GPIO_CRL_MODE4;											//Input floating mode PA4
}

void MCO_out(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8_0;
	GPIOA->CRH |= GPIO_CRH_CNF8_1;
	GPIOA->CRH |= GPIO_CRH_MODE8;
	
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
	
}

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
		
		if((GPIOA->IDR & GPIO_IDR_IDR4) != 0)
			{
				
				vTaskDelay(170);
				GPIOC->ODR ^= GPIO_ODR_ODR12; 		// ~ PC12
				USART3_Send_String("Button\r\n");
				
			}
			
			vTaskDelay(100);
			
	}
	
}

void USART3_Init()
{	
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; 		//Takt on for port D
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;			//Takt on Alternate function IO
	AFIO->MAPR |= AFIO_MAPR_USART3_REMAP;		//Full Remap USART3 PD8-TX, PD9-RX
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;		//Enable clock on USART3

	GPIOD->CRH &= ~GPIO_CRH_CNF8_0;				//PD8 Alternate Push-pull
	GPIOD->CRH |= GPIO_CRH_CNF8_1;				//PD8 Alternate Push-pull
	GPIOD->CRH |= GPIO_CRH_MODE8;				//PD8 50MHz

	GPIOD->CRH &= ~GPIO_CRH_CNF9_1;				//Input floating mode PD9
	GPIOD->CRH |= GPIO_CRH_CNF9_0;				//Input floating mode PD9
	GPIOD->CRH &= ~GPIO_CRH_MODE9;				//Input floating mode PD9

	USART3->BRR = 0x9C4;						//=(fapb1+baudrate/2)/baudrate

	USART3->CR1 |= USART_CR1_TE;				//USART3 Transmit EN
	USART3->CR1 |= USART_CR1_RE;				//USART3 Receive EN
	USART3->CR1 |= USART_CR1_UE;				//USART3 EN

	USART3->CR1 |= USART_CR1_RXNEIE;			//Включаем прерывание по приему
	NVIC_EnableIRQ(USART3_IRQn);				//Вектор прерывания для USART3
}

void USART3_Send(char chr)
{
	while(!(USART3->SR & USART_SR_TC));
	USART3->DR = chr;
}

void USART3_Send_String(char* str)
{
	uint8_t i = 0;
	while(str[i])
	USART3_Send(str[i++]);
}

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