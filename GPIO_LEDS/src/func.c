/*
 * func.c
 *
 *  Created on: 03.10.2018
 *      Author: mikol
 */
#include "func.h"


void GPIO_Conf()
{
	 GPIO_InitTypeDef gpio;

	 GPIO_StructInit(&gpio);
	 gpio.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	 gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOE, &gpio);

	 gpio.GPIO_Pin = GPIO_Pin_15;
	 gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	 GPIO_Init(GPIOF, &gpio);
}

void EXTI_Conf()
{
	EXTI_InitTypeDef exti;

	EXTI_StructInit(&exti);
	exti.EXTI_Line = EXTI_Line15;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;

	EXTI_Init(&exti);
}

void NVIC_Conf()
{
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic);
}


