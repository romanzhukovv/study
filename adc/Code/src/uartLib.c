/***************************Library*******************************/

#include "uartLib.h"

/*************************Functions*******************************/

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

void SendDataUSART3 (uint8_t data){

	while (!(USART3->SR & USART_SR_TC));
	USART3->DR = data;
	
}