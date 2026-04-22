/*
 * DIO_interface.h
 *
 *  Created on: Aug 25, 2025
 *      Author: hp
 */
#ifndef DIO_interface
#define DIO_interface

#include"../../Macros/std_type.h"
#include "DIO_private.h"
#include"../../Macros/BIT_MATH.h"

#define NUM_OF_PINS_PER_PORT 8
#define NUM_OF_PORTS 4

// PINS
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7


//PORTS
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

/* Pin direction declaration */
typedef enum{
	PIN_INPUT, PIN_OUTPUT
}DIO_PinDirectionType;

/* Port direction declaration */
typedef enum{
	PORT_INPUT, PORT_OUTPUT = 0xff
}DIO_PortDirectionType;



void DIO_vSetPortDir(u8 Copy_u8PortNum,u8 Copy_u8PortDirection);
void DIO_voidSetPinDirection(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinDirection);

void DIO_voidSetPortValue(u8 Copy_u8PortNum,u8 Copy_u8PortValue);
void DIO_voidSetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinValue);


u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);

void DIO_writePortMasked(u8 portNum, u8 value, u8 mask);
void DIO_setupPortDirectionMasked(u8 portNum, u8 direction, u8 mask);


#endif
