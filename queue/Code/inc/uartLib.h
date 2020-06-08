/***************************Library*******************************/

#include "stm32f1xx.h"

/*************************Functions*******************************/

void USART3_Init(void);
void USART3_Send(char chr);
void USART3_Send_String(char* str);
void SendDataUSART3 (uint8_t data);