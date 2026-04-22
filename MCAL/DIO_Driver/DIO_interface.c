/*
 * DIO_interface.c
 *
 *  Created on: Aug 25, 2025
 *      Author: hp
 */
#include "DIO_interface.h"

volatile u8* const DDR_REG[NUM_OF_PORTS]  = { &DDRA, &DDRB, &DDRC, &DDRD };
volatile u8* const PORT_REG[NUM_OF_PORTS] = { &PORTA, &PORTB, &PORTC, &PORTD };
volatile u8* const PIN_REG[NUM_OF_PORTS]  = { &PINA, &PINB, &PINC, &PIND };


void DIO_vSetPortDir(u8 Copy_u8PortNum,u8 Copy_u8PortDirection){
	if(Copy_u8PortNum >= NUM_OF_PORTS){
		return;
	}else{
		*DDR_REG[Copy_u8PortNum] = Copy_u8PortDirection;
	}
}


void DIO_voidSetPinDirection(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinDirection){
	if(Copy_u8PortNum >= NUM_OF_PORTS || Copy_u8PinNum >= 8){
		return;
	}else{
		if(Copy_u8PinDirection) SET_BIT(*DDR_REG[Copy_u8PortNum], Copy_u8PinNum);
		else CLEAR_BIT(*DDR_REG[Copy_u8PortNum], Copy_u8PinNum);
	}
}


void DIO_voidSetPortValue(u8 Copy_u8PortNum,u8 Copy_u8PortValue){
	if(Copy_u8PortNum >= NUM_OF_PORTS){
		return;
	}else{
		*PORT_REG[Copy_u8PortNum] = Copy_u8PortValue;
	}
}


void DIO_voidSetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinValue){
	if(Copy_u8PortNum >= NUM_OF_PORTS || Copy_u8PinNum >= 8){
		return;
	}else{
		if(Copy_u8PinValue) SET_BIT(*PORT_REG[Copy_u8PortNum], Copy_u8PinNum);
		else CLEAR_BIT(*PORT_REG[Copy_u8PortNum], Copy_u8PinNum);
	}
}


u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    if(Copy_u8Port >= NUM_OF_PORTS || Copy_u8Pin >= 8){
        return 0;
    }
    return GET_BIT(*PIN_REG[Copy_u8Port], Copy_u8Pin);
}



u8 DIO_u8ReadPortValue(u8 Copy_u8PortNum){
	if(Copy_u8PortNum >= NUM_OF_PORTS){
		return 0;
	}else{
		return *PIN_REG[Copy_u8PortNum];
	}
}



void DIO_writePortMasked(u8 portNum, u8 value, u8 mask){

	if(portNum >= NUM_OF_PORTS)
	{
		/* do nothing */
	}
	else
	{
		u8 currentValue = *PORT_REG[portNum]; // read current PORT value
		u8 newValue = (currentValue & ~mask) | (value & mask);
		*PORT_REG[portNum] = newValue;
	}
}



void DIO_setupPortDirectionMasked(u8 portNum, u8 direction, u8 mask){
	if(portNum >= NUM_OF_PORTS){
		/* Do nothing */
	}
	else {
		u8 currentDDR = *DDR_REG[portNum];
		u8 newDDR = (currentDDR & ~mask) | (direction & mask);
		*DDR_REG[portNum] = newDDR;
	}
}
