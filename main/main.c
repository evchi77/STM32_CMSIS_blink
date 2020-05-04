/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Vsevolod
 * @brief          : Main program body
 * @date           : 04.05.2020 18:56
 ******************************************************************************
 */

/* Includes -----------------------------------------------------------------*/
#include "main.h"
#include "clock.h"
#include "led.h"

/* Private types ------------------------------------------------------------*/


/* Private variables --------------------------------------------------------*/


/* Private functions prototypes ---------------------------------------------*/
static void init_all(void);
static void example_blinker_init(void);
static void example_timer_init(void);
static void example_timer_interrupt_enable(void);
static void delay_cycles(uint32_t i);

/* Private defines ----------------------------------------------------------*/


/* Private macros -----------------------------------------------------------*/


/* MAIN FUNCTION ------------------------------------------------------------*/
int main(void)
{
	init_all();

	__enable_irq();	// Global interrupt enable

	while(1)
	{
		delay_cycles(800000);
		led_led0_switch();
	}
}

/* Private functions --------------------------------------------------------*/
static void init_all(void)
{
	clock_init();
	led_init();
	example_blinker_init();
	example_timer_init();
	example_timer_interrupt_enable();
	return;
}

static void example_blinker_init(void)
{
	GPIOA->MODER 	|= GPIO_MODER_MODER1_1;	// Set PA1 to AF mode
	GPIOA->AFR[0] 	|= GPIO_AFRL_AFSEL1_1;	// Set PA1 to AF2

	return;
}

static void example_timer_init(void)
{
// Will use TIM5 for PWM

	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;			// Enable TIM5 clock

	TIM5->CR1 |= TIM_CR1_ARPE;					// ARR auto-preload enable
	TIM5->CCMR1 |= 0b110 << TIM_CCMR1_OC2M_Pos;	// Output compare mode PWM1
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE;				// CCR2 preload enable
	TIM5->CCMR1 |= 0b00 << TIM_CCMR1_CC2S_Pos;	// CC2 as output
	TIM5->CCER |= TIM_CCER_CC2E;				// Output 2 enable

	TIM5->PSC = (uint16_t)0;					// Prescaler
	TIM5->ARR = (uint32_t)255;					// Upper limit
	TIM5->CCR2 = (uint32_t)20;					// Output compare
	

	TIM5->EGR |= TIM_EGR_UG;					// Update (init shadow registers)
	TIM5->CR1 |= TIM_CR1_CEN;					// Count enable

	return;
}

static void example_timer_interrupt_enable(void)
{
// Will use TIM6 for generating interupts

	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;			// Enable TIM6 clock

	TIM6->CR1 |= TIM_CR1_ARPE;					// ARR auto-preload enable
	TIM6->DIER |=  TIM_DIER_UIE;				// Update interrupt enable

	TIM6->PSC = (uint16_t)64000;				// Prescaler; => 250 Hz
	TIM6->ARR = (uint16_t)250;					// => update every 1 s

	TIM6->EGR |= TIM_EGR_UG;					// Update (init shadow registers)
	TIM6->CR1 |= TIM_CR1_CEN;					// Counter enable

	NVIC_EnableIRQ(TIM6_DAC_IRQn);				// Enable interrupt in NVIC

	return;
}

inline static void delay_cycles(uint32_t i)
{
	for(; i > 0; --i);
}