#include "stm32f10x.h"

void send_char(char c)
{
 while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 USART_SendData(USART1, c);
}

void send_string(const char* s)
{
 while (*s)
 send_char(*s++);
}

int main(void)
{
 GPIO_InitTypeDef gpio;
 USART_InitTypeDef uart;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

 GPIO_StructInit(&gpio);
 gpio.GPIO_Pin = GPIO_Pin_9;
 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
 GPIO_Init(GPIOA, &gpio);

 gpio.GPIO_Pin = GPIO_Pin_10;
 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_Init(GPIOA, &gpio);

 USART_StructInit(&uart);
 uart.USART_BaudRate = 9600;
 USART_Init(USART1, &uart);

 USART_Cmd(USART1, ENABLE);

 while (1) {
 send_string("Hello world!\r\n");
 }
}
