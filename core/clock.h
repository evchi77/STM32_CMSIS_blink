/**
 ******************************************************************************
 * @file           : clock.h
 * @author         : Vsevolod
 * @brief          : 
 * @date           : 04.05.2020 19:08
 ******************************************************************************
 */

#ifndef CLOCK_H_
#define CLOCK_H_

/* Includes -----------------------------------------------------------------*/


/* Public types -------------------------------------------------------------*/


/* Public variables ---------------------------------------------------------*/
extern uint32_t   HCLK,
                  cortex_sys_tim,
                  APB1_periph,
                  APB1_tim,
                  APB2_periph,
                  APB2_tim;

/* Public functions prototypes ----------------------------------------------*/
// Clocks initialization
void clock_init(void);
// Update variables containing clocks' frequencies
void clock_update(void);

/* Public defines -----------------------------------------------------------*/


/* Public macros ------------------------------------------------------------*/


#endif /* CLOCK_H_ */
