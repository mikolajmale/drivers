/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f10x.h"
#include <stdio.h>

volatile uint32_t timer_ms = 0;

void SysTick_Handler()
{
 if (timer_ms) {
 timer_ms--;
 }
}

void delay_ms(int time)
{
 timer_ms = time;
 while (timer_ms) {};
}

void send_char(char c)
{
 while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 USART_SendData(USART1, c);
}

int __io_putchar(int c)
{
 if (c=='\n')
 send_char('\r');
 send_char(c);
 return c;
}

void RCC_Conf()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void ADC_Conf()
{
	ADC_InitTypeDef adc;

	ADC_StructInit(&adc);
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_NbrOfChannel = 1;
	adc.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&adc);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_71Cycles5);

	ADC_Cmd(ADC1 , ENABLE);
}

void ADC_Calibration()
{
	ADC_ResetCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
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

	 gpio.GPIO_Pin = GPIO_Pin_0;
	 gpio.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_Init(GPIOA , &gpio);


}

void UART_Conf()
{
	 USART_InitTypeDef uart;

	 USART_StructInit(&uart);
	 uart.USART_BaudRate = 9600;
	 USART_Init(USART1, &uart);

	 USART_Cmd(USART1, ENABLE);
}

int main(void)
{

	RCC_Conf();
	GPIO_Conf();
	UART_Conf();
	ADC_Conf();
	ADC_Calibration();


	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	SysTick_Config(SystemCoreClock / 1000);

	for(;;)
	{
		uint16_t adc;
		adc = ADC_GetConversionValue(ADC1);
		printf("voltage: %d V\n",adc);
		delay_ms(500);

	}
}
