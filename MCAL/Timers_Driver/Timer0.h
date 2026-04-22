/*
 * Timer0.h
 *
 *  Created on: Sep 4, 2025
 *      Author: hp
 */

#ifndef MCAL_TIMERS_DRIVER_TIMER0_H_
#define MCAL_TIMERS_DRIVER_TIMER0_H_

#include "Timer_config.h"
#include "Timer_private.h"
#include "../../Macros/std_type.h"

#define TIMER0_PRELOAD 256
#define TIMER0_OF_INTERRUPT_ENABLE True
#define TIMER0_CTC_INTERRUPT_ENABLE True


typedef enum{
	OC0_CTC_NORMAL, TOGGLE_OC0, CLEAR_OC0, SET_OC0
}TIMER0_CTC_MODE_SELECT;


void TIMER0_OF_init(CLK_SELECT clk);
void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, CLK_SELECT clk, u8 compValue);

void TIMER0_FAST_PWM_init(FAST_PWM_MODES mode, CLK_SELECT clk); //اللي استخدمناها في السيرفو
void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle);

void TIMER0_PHASE_PWM_init(PHASE_PWM_MODES mode, CLK_SELECT clk);
void TIMER0_PHASE_PWM_set_dutyCycle(u8 dutyCycle);

void TIMER0_OF_set_cb(void (*cb)(void));
void TIMER0_CTC_set_cb(void (*cb)(void));

void TIMER0_VoidInit(void);

#endif /* MCAL_TIMERS_DRIVER_TIMER0_H_ */
