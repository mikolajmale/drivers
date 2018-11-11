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

#include "math.h"
#include "stm32f10x.h"
volatile uint32_t timer_ms = 0;

void SysTick_Handler()
{
 if (timer_ms)
 timer_ms--;
}

void delay_ms(int time)
{
 timer_ms = time;
 while (timer_ms);
}

void RCC_Conf(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
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

	 gpio.GPIO_Pin = PWM3;
	 gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	 gpio.GPIO_Speed = GPIO_Speed_50MHz;
		 GPIO_Init(GPIOB, &gpio);

}
void Timer3_Conf(void)
{
	 TIM_TimeBaseInitTypeDef tim;
	 TIM_OCInitTypeDef  channel;

	TIM_TimeBaseStructInit(&tim);
	 tim.TIM_CounterMode = TIM_CounterMode_Up;
	 tim.TIM_Prescaler = 64 - 1;
	 tim.TIM_Period = 1000 - 1;
	 TIM_TimeBaseInit(TIM3, &tim);

	 TIM_OCStructInit(&channel);
	 channel.TIM_OCMode = TIM_OCMode_PWM2;
	 channel.TIM_OutputState = TIM_OutputState_Enable;
	 TIM_OC1Init(TIM3, &channel);
	 TIM_OC2Init(TIM3, &channel);
	 TIM_OC3Init(TIM3, &channel);

	 TIM_Cmd(TIM3, ENABLE);
}

float calc_pwm(float val)
{
 const float k = 0.1f;
 const float x0 = 60.0f;
 return 500.0f / (1.0f + exp(-k * (val - x0)));
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
	Timer3_Conf();

	int counter = 0;
	SysTick_Config(SystemCoreClock / 1000);

		while (1) {
		    float r = 50 * (1.0f + sin(counter / 100.0f));
		    float g = 50 * (1.0f + sin(1.5f * counter / 100.0f));
		    float b = 50 * (1.0f + sin(2.0f * counter / 100.0f));
		    TIM_SetCompare1(TIM3, calc_pwm(b));
		    TIM_SetCompare2(TIM3, calc_pwm(g));
		    TIM_SetCompare3(TIM3, calc_pwm(r));

		    delay_ms(20);
		    counter++;
		}


}
