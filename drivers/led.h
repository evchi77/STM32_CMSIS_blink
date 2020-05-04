/**
 ******************************************************************************
 * @file           : led.h
 * @author         : Vsevolod
 * @brief          : LED-specific routines & definitions
 * @date           : 04.05.2020 19:16
 ******************************************************************************
 */

#ifndef LED_H_
#define LED_H_

/* Includes -----------------------------------------------------------------*/


/* Public types -------------------------------------------------------------*/


/* Public variables ---------------------------------------------------------*/


/* Public functions prototypes ----------------------------------------------*/
// Init LEDs
void led_init(void);

// Turn LED0 on
void led_led0_on(void);

// Turn LED1 on
void led_led1_on(void);

// Turn LED2 on
void led_led2_on(void);

// Turn LED0 off
void led_led0_off(void);

// Turn LED1 off
void led_led1_off(void);

// Turn LED2 off
void led_led2_off(void);

// Switch LED0
void led_led0_switch(void);

// Switch LED1
void led_led1_switch(void);

// Switch LED2
void led_led2_switch(void);

/* Public defines -----------------------------------------------------------*/


/* Public macros ------------------------------------------------------------*/


#endif /* LED_H_ */
