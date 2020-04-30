/*
 * clock.h
 *
 *     Created: 21.04.2020 21:33:50
 *      Author: Vsevolod
 *       Brief: Clocks initialization routines
 */

#ifndef CLOCK_H_
#define CLOCK_H_

/*** Global variables ***/
extern uint32_t   HCLK,
                  cortex_sys_tim,
                  APB1_periph,
                  APB1_tim,
                  APB2_periph,
                  APB2_tim;
/************************/

/*** Users functions ***/
// Clocks initialization
void clock_init(void);
// Update variables containing clocks' frequencies
void clock_update(void);
/***********************/

/*** Internal/system functions ***/
// Reset RCC registers
void __clock_reset_all(void); 

// Set system clock
void __clock_set_sys(void);

// Set peripheral clocks
void __clock_set_periph(void);
/*********************************/

/*** Definitions ***/
// HSE_VALUE, HSI_VALUE, LSE_VALUE, LSI_VALUE defined in system_stm32f4xx.h

#define HSE_STARTUP_TIMEOUT		1000
#define LSE_STARTUP_TIMEOUT		5000

#endif /* CLOCK_H_ */
