/*
 * Timer_config.h
 *
 *  Created on: Sep 4, 2025
 *      Author: hp
 */

#ifndef MCAL_TIMERS_DRIVER_TIMER_CONFIG_H_
#define MCAL_TIMERS_DRIVER_TIMER_CONFIG_H_

typedef enum{
	NORMAL, PWM_PHASE_CORRECT, CTC, FAST_PWM
}WV_MODES;


typedef enum{
	FAST_PWM_NORMAL, NON_INVERTING_MODE, INVERTING_MODE
}FAST_PWM_MODES;

typedef enum{
	PHASE_PWM_NORMAL, ClrUp_SetDown, SetUp_ClrDown
}PHASE_PWM_MODES;

typedef enum{
	NO_CLK, NO_PRE, PRE_8, PRE_64, PRE_256, PRE_1024
}CLK_SELECT;



#endif /* MCAL_TIMERS_DRIVER_TIMER_CONFIG_H_ */
