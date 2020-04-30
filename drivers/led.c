/*
 * led.c
 *
 *     Created: 21.04.2020 20:35:05
 *      Author: Vsevolod
 *       Brief: LED-specific routines
 */ 

/*** Includes ***/
#include "led.h"
#include "main.h"
/****************/

/*** Users functions ***/
// Init LEDs
void led_init(void)
{
    // Configure PA0, PA1, PA2 as GP outputs:
    GPIOA->MODER |= GPIO_MODER_MODER0_0 |   // Set MODER0[1:0] = 01
                /*    GPIO_MODER_MODER1_0 |   // Set MODER1[1:0] = 01 */    // reserved for PWM example
                    GPIO_MODER_MODER2_0;	// Set MODER2[1:0] = 01
    return;
}

// Turn LED0 on
void led_led0_on(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS0;		// Set PA0 high
    return;
}

// Turn LED1 on
void led_led1_on(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS1;		// Set PA1 high
    return;
}

// Turn LED2 on
void led_led2_on(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS2;		// Set PA2 high
    return;
}

// Turn LED0 off
void led_led0_off(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR0;		// Set PA0 low
    return;
}

// Turn LED1 off
void led_led1_off(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR1;		// Set PA1 low
    return;
}

// Turn LED2 off
void led_led2_off(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR2;		// Set PA2 low
    return;
}

// Switch LED0
void led_led0_switch(void)
{
    GPIOA->ODR ^= GPIO_ODR_OD0;         // Change state of PA0
    return;
}

// Switch LED1
void led_led1_switch(void)
{
    GPIOA->ODR ^= GPIO_ODR_OD1;         // Change state of PA1
    return;
}

// Switch LED2
void led_led2_switch(void)
{
    GPIOA->ODR ^= GPIO_ODR_OD2;         // Change state of PA2
    return;
}
/***********************/

/*** Internal/system functions ***/

/*********************************/
