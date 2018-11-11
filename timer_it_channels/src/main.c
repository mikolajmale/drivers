/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#define PWM1 GPIO_Pin_6
#define PWM2 GPIO_Pin_7
#define PWM3 GPIO_Pin_0
#define PWM4 GPIO_Pin_1

#include "stm32f10x.h"
			
void RCC_Conf(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void GPIO_Conf()
{
	 GPIO_InitTypeDef gpio;

	 GPIO_StructInit(&gpio);
	 gpio.GPIO_Pin = GPIO_Pin_9;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 GPIO_Init(GPIOA, &gpio);

	 gpio.GPIO_Pin = GPIO_Pin_10;
	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOA, &gpio);

	 gpio.GPIO_Pin = PWM1 | PWM2;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpio.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &gpio);

	 gpio.GPIO_Pin = PWM3 | PWM4;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpio.GPIO_Speed = GPIO_Speed_50MHz;
		 GPIO_Init(GPIOB, &gpio);

	 gpio.GPIO_Pin = GPIO_Pin_7;
		 gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		 GPIO_Init(GPIOE, &gpio);
}
void Timer3_Conf(void)
{
	TIM_TimeBaseInitTypeDef tim3;

	TIM_TimeBaseStructInit(&tim3);
	tim3.TIM_Period = 2000 - 1;
	tim3.TIM_Prescaler = 36 - 1;
	tim3.TIM_ClockDivision = TIM_CKD_DIV1;
	tim3.TIM_CounterMode = TIM_CounterMode_Up;
	tim3.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM3 , &tim3);

	TIM_OCInitTypeDef channel;

	TIM_OCStructInit(&channel);
	channel.TIM_OCMode = TIM_OCMode_PWM1;
	channel.TIM_OutputState  = TIM_OutputState_Enable;
	channel.TIM_Pulse = 200;
	TIM_OC1Init(TIM3, &channel);

	channel.TIM_Pulse = 400;
	TIM_OC2Init(TIM3, &channel);

	channel.TIM_Pulse = 1000;
	TIM_OC3Init(TIM3, &channel);

	channel.TIM_Pulse = 2000;
	TIM_OC4Init(TIM3, &channel);


	//TIM_ITConfig(TIM3 , TIM_IT_Update | TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 , ENABLE);
	TIM_Cmd(TIM3 , ENABLE);
}

void NVIConf()
{
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannel = TIM3_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;

	NVIC_Init(&nvic);
}

void UART_Conf()
{
	 USART_InitTypeDef uart;

	 USART_StructInit(&uart);
	 uart.USART_BaudRate = 9600;
	 USART_Init(USART1, &uart);

	 USART_Cmd(USART1, ENABLE);
}

//void TIM3_IRQHandler()
//{
// if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
// {
// TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//
// if (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_7))
// {
//	 GPIO_ResetBits(GPIOE, GPIO_Pin_7);
// }
// else
// {
//	 GPIO_SetBits(GPIOE, GPIO_Pin_7);
// }
//
// GPIO_SetBits(GPIOA, PWM1 | PWM2);
// GPIO_SetBits(GPIOB, PWM3 | PWM4);
// }
//
// if (TIM_GetITStatus(TIM3, TIM_IT_CC1) == SET)
// {
// TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
// GPIO_ResetBits(GPIOA, PWM1);
//
// }
// if (TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET)
// {
// TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
// GPIO_ResetBits(GPIOA, PWM2);
//
// }
// if (TIM_GetITStatus(TIM3, TIM_IT_CC3) == SET)
// {
// TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
// GPIO_ResetBits(GPIOB, PWM3);
//
// }
// if (TIM_GetITStatus(TIM3, TIM_IT_CC4) == SET)
// {
// TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
// GPIO_ResetBits(GPIOB, PWM4);
//
// }
//}

int main(void)
{
	RCC_Conf();
	GPIO_Conf();
	UART_Conf();
	Timer3_Conf();
	//NVIConf();

	for(;;);
}
