#include "stm32f10x.h"
#include "func.h"

volatile uint32_t timer_ms = 0;

void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line15))
	{
		if(GPIO_ReadInputDataBit(GPIOF , GPIO_Pin_15) == 0)
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_8);
		}
		else
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);
		}
	}

	EXTI_ClearITPendingBit(EXTI_Line15);
}

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

int main(void)
{
 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);

 GPIO_Conf();
 EXTI_Conf();
 NVIC_Conf();

 SysTick_Config(SystemCoreClock / 1000);


 while (1)
{

}

}
