/*
 * Timer0.c
 *
 *  Created on: Sep 4, 2025
 *      Author: hp
 */

#include "../DIO_Driver/DIO_interface.h"
#include "../External_Interrupts_Driver/INT_interface.h"
#include "Timer0.h"
#include "../../Macros/std_type.h"

#include <avr/interrupt.h>

void (*TIMER_OF_cb)(void) =  NULL_PTR;
void (*TIMER_CTC_cb)(void) =  NULL_PTR;

static void TIMER0_clockSelect(CLK_SELECT clck);


void TIMER0_OF_init(CLK_SELECT clk){
	TCNT0 = TIMER0_PRELOAD;
		SET_BIT(TCCR0, FOC0);
		CLEAR_BIT(TCCR0, WGM01);
		CLEAR_BIT(TCCR0, WGM00);

		TIMER0_clockSelect(clk);

	#if (TIMER0_OF_INTERRUPT_ENABLE == True)
		SET_BIT(TIMSK, TOIE0);
		EXT_interrupt_GIE_state(ENABLE);
	#else
		while( BIT_IS_CLEAR(TIFR, TOV0) );
		SET_BIT(TIFR, TOV0);
		TCNT0 = 0;
	#endif

}

void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, CLK_SELECT clk, u8 compValue){
	TCNT0 = TIMER0_PRELOAD;
		OCR0 = compValue;

		SET_BIT(TCCR0, FOC0);
		SET_BIT(TCCR0, WGM01);
		CLEAR_BIT(TCCR0, WGM00);

		switch(mode){
		case OC0_CTC_NORMAL:
			CLEAR_BIT(TCCR0, COM01);
			CLEAR_BIT(TCCR0, COM00);
			break;
		case TOGGLE_OC0:
			CLEAR_BIT(TCCR0, COM01);
			SET_BIT(TCCR0, COM00);
			break;
		case CLEAR_OC0:
			SET_BIT(TCCR0, COM01);
			CLEAR_BIT(TCCR0, COM00);
			break;
		case SET_OC0:
			SET_BIT(TCCR0, COM01);
			SET_BIT(TCCR0, COM00);
			break;
		}

		TIMER0_clockSelect(clk);

	#if(TIMER0_CTC_INTERRUPT_ENABLE == True)
		SET_BIT(TIMSK, OCIE0);
		EXT_interrupt_GIE_state(ENABLE);
	#else
		while(BIT_IS_CLEAR(TIFR, OCF0));
		SET_BIT(TIFR, OCF0);
		TCCR0 = 0;
	#endif

}

void TIMER0_FAST_PWM_init(FAST_PWM_MODES mode, CLK_SELECT clk){
	TCNT0 = TIMER0_PRELOAD;
	OCR0 = 0;

	CLEAR_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

	switch(mode){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case NON_INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clk);

}


//    // Enable OV interrupt
//    SET_BIT(TIMSK, TOIE0);
//
//    // Enable GIE
//    SET_BIT(SREG, PIN7);



void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle){
	OCR0 = dutyCycle;
}

void TIMER0_PHASE_PWM_init(PHASE_PWM_MODES mode, CLK_SELECT clk){
	TCNT0 = TIMER0_PRELOAD;
	OCR0 = 0;

	CLEAR_BIT(TCCR0, FOC0);
	CLEAR_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

	switch(mode){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case ClrUp_SetDown:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case SetUp_ClrDown:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clk);

}
void TIMER0_PHASE_PWM_set_dutyCycle(u8 dutyCycle){
	OCR0 = dutyCycle;
}


void TIMER0_OF_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_OF_cb = cb;
}
void TIMER0_CTC_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_CTC_cb = cb;
}

void TIMER0_clockSelect(CLK_SELECT clock){
	switch(clock){
	case NO_CLK:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;
	case NO_PRE:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case PRE_8:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRE_64:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case PRE_256:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRE_1024:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;
	}
}

ISR(TIMER0_OVF_vect){
	if(TIMER_OF_cb != NULL_PTR) TIMER_OF_cb();
}


ISR(TIMER0_COMP_vect){
	if(TIMER_CTC_cb != NULL_PTR) TIMER_CTC_cb();
}




