/*
 * led.h
 *
 *     Created: 21.04.2020 20:32:45
 *      Author: Vsevolod
 *       Brief: LED-specific routines & definitions
 */

#ifndef LED_H_
#define LED_H_

/*** Users functions ***/
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
/***********************/

/*** Internal/system functions ***/

/*********************************/

/*** Definitions ***/

#endif /* LED_H_ */
