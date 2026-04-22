/*
 * INT_interface.c
 *
 *  Created on: Sep 1, 2025
 *      Author: hp
 */
#include "INT_interface.h"
#include <avr/interrupt.h>

void (*ptr_cb0)(void) = NULL_PTR;
void (*ptr_cb1)(void) = NULL_PTR;
void (*ptr_cb2)(void) = NULL_PTR;


void EXT_interrupt_GIE_state(INT_STATE state){
	switch(state){
	case ENABLE:
		SET_BIT(SREG, I_BIT);
		break;
	case DISABLE:
		CLEAR_BIT(SREG, I_BIT);
		break;
	}

}

/* initialize interrupt 0 */
void EXT_INT0_init(INT_STATE state, INT_CONTROL ctrl){
	switch(state){
	case ENABLE:
		SET_BIT(GICR, INT0);
		break;
	case DISABLE:
		CLEAR_BIT(GICR, INT0);
		break;
	}

	switch(ctrl){
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR, ISC01);
			CLEAR_BIT(MCUCR, ISC00);
			break;
		case ANY_CHANGE:
			CLEAR_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
		case FALLING_EDGE:
			SET_BIT(MCUCR, ISC01);
			CLEAR_BIT(MCUCR, ISC00);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
			break;
		}
}

void EXT_int0_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR){
		ptr_cb0 = cb;
	}

}

ISR(INT0_vect){
	if(ptr_cb0 != NULL_PTR){
		ptr_cb0();
	}
}

/* initialize interrupt 1 */
void EXT_INT1_init(INT_STATE state, INT_CONTROL ctrl){
	switch(state){
	case ENABLE:
		SET_BIT(GICR, INT1);
		break;
	case DISABLE:
		CLEAR_BIT(GICR, INT1);
		break;
	}

	switch(ctrl){
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR, ISC11);
			CLEAR_BIT(MCUCR, ISC10);
			break;
		case ANY_CHANGE:
			CLEAR_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
		case FALLING_EDGE:
			SET_BIT(MCUCR, ISC11);
			CLEAR_BIT(MCUCR, ISC10);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
			break;
		}
}

void EXT_int1_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR){
		ptr_cb1 = cb;
	}

}

ISR(INT1_vect){
	if(ptr_cb1 != NULL_PTR){
		ptr_cb1();
	}
}

/* initialize interrupt 2 */
void EXT_INT2_init(INT_STATE state, INT_CONTROL ctrl){
	switch(state){
	case ENABLE:
		SET_BIT(GICR, INT2);
		break;
	case DISABLE:
		CLEAR_BIT(GICR, INT2);
		break;
	}

	switch(ctrl){
		case FALLING_EDGE:
			CLEAR_BIT(MCUCSR, ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR, ISC2);
			break;
		}
}

void EXT_int2_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR){
		ptr_cb2 = cb;
	}

}

ISR(INT2_vect){
	if(ptr_cb2 != NULL_PTR){
		ptr_cb2();
	}
}
