/**
 ******************************************************************************
 * @file           : interrupts.c
 * @author         : Vsevolod
 * @brief          : Interrupt procedures
 * @date           : 04.05.2020 18:58
 ******************************************************************************
 */

/* Includes (referenced modules should be included here as well)-------------*/
#include "main.h"
#include "led.h"

void TIM6_DAC_IRQHandler(void)
{
	led_led2_switch();

	TIM6->SR &= ~(TIM_SR_UIF);	// Clear interrupt flag is mandatory!
	return;
}
