#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "../../MCAL/External_Interrupts_Driver/INT_interface.h"
#include "../../Macros/std_type.h"

void (*TIMER1_OF_cb)(void) = NULL_PTR;
void (*TIMER1_CTC_cb)(void) = NULL_PTR;

static void TIMER1_clockSelect(CLK_SELECT clock);

void TIMER1_OF_init(CLK_SELECT clock){
	TCNT1 = TIMER1_PRELOAD;
	TCCR1A = 0;
	CLEAR_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

	TIMER1_clockSelect(clock);

#if (TIMER1_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE1);
	EXT_interrupt_GIE_state(ENABLE);
#else
	while(BIT_IS_CLEAR(TIFR, TOV1));
	SET_BIT(TIFR, TOV1);
	TCNT1 = 0;
#endif
}

void TIMER1_CTC_init(TIMER1_CTC_MODE_SELECT mode, CLK_SELECT clock, u16 compValueA){
	TCNT1 = TIMER1_PRELOAD;
	OCR1A = compValueA;

	CLEAR_BIT(TCCR1A, WGM10);
	CLEAR_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

	switch(mode){
	case OC1_CTC_NORMAL:
		CLEAR_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		break;
	case TOGGLE_OC1:
		CLEAR_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		break;
	case CLEAR_OC1:
		SET_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		break;
	case SET_OC1:
		SET_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		break;
	}

	TIMER1_clockSelect(clock);

#if (TIMER1_CTC_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE1A);
	EXT_interrupt_GIE_state(ENABLE);
#else
	while(BIT_IS_CLEAR(TIFR, OCF1A));
	SET_BIT(TIFR, OCF1A);
	TCCR1A = 0;
	TCCR1B = 0;
#endif
}

void TIMER1_FAST_PWM_init(FAST_PWM_MODES mode, CLK_SELECT clock, u16 topValue){
	TCNT1 = 0;
	ICR1 = topValue;   // Top value

	// Fast PWM mode 14: WGM13:0 = 1110 -> ICR1 is TOP
	CLEAR_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);

	// OC1A
	switch(mode){
	case NON_INVERTING_MODE:
		SET_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		break;
	case INVERTING_MODE:
		SET_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		break;
	}

	TIMER1_clockSelect(clock);
}

void TIMER1_FAST_PWM_set_dutyCycle_A(u16 dutyCycle){
	OCR1A = dutyCycle;
}

void TIMER1_FAST_PWM_set_dutyCycle_B(u16 dutyCycle){
	OCR1B = dutyCycle;
}

void TIMER1_OF_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER1_OF_cb = cb;
}

void TIMER1_CTC_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER1_CTC_cb = cb;
}

static void TIMER1_clockSelect(CLK_SELECT clock){
	switch(clock){
	case NO_CLK:
		CLEAR_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;
	case NO_PRE:
		CLEAR_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;
	case PRE_8:
		CLEAR_BIT(TCCR1B, CS12);
		SET_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;
	case PRE_64:
		CLEAR_BIT(TCCR1B, CS12);
		SET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;
	case PRE_256:
		SET_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;
	case PRE_1024:
		SET_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;
	}
}

/* ------------------ ISRs ------------------ */
ISR(TIMER1_OVF_vect){
	if(TIMER1_OF_cb != NULL_PTR) TIMER1_OF_cb();
}

ISR(TIMER1_COMPA_vect){
	if(TIMER1_CTC_cb != NULL_PTR) TIMER1_CTC_cb();
}
