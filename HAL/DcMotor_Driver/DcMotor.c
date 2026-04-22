/*
 * DcMotor.c
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */
#include "../../MCAL/DIO_Driver/DIO_interface.h"
#include "../../Macros/BIT_MATH.h"
#include "DcMotor.h"

void MOTOR_Init(void)
{
	MOTOR_DDR |= (1<<MOTOR_IN1) | (1<<MOTOR_IN2) | (1<<MOTOR_EN); //pins as output
}

void MOTOR_Forward(void)
{
	DIO_voidSetPinDirection(PORT_A, PIN_0, PIN_OUTPUT);
	DIO_voidSetPinValue(PORT_A, PIN_0, HIGH);

	SET_BIT(MOTOR_PORT, MOTOR_IN1);
	CLEAR_BIT(MOTOR_PORT, MOTOR_IN2);
	SET_BIT(MOTOR_PORT, MOTOR_EN);
}

void MOTOR_Backward(void)
{
	DIO_voidSetPinDirection(PORT_A, PIN_0, PIN_OUTPUT);
	DIO_voidSetPinValue(PORT_A, PIN_0, HIGH);

	CLEAR_BIT(MOTOR_PORT, MOTOR_IN1);
	SET_BIT(MOTOR_PORT, MOTOR_IN2);
	SET_BIT(MOTOR_PORT, MOTOR_EN);
}

void MOTOR_Stop(void)
{
	DIO_voidSetPinDirection(PORT_A, PIN_1, PIN_OUTPUT);
	DIO_voidSetPinValue(PORT_A, PIN_1, HIGH);

	CLEAR_BIT(MOTOR_PORT, MOTOR_IN1);
	CLEAR_BIT(MOTOR_PORT, MOTOR_IN2);
	CLEAR_BIT(MOTOR_PORT, MOTOR_EN);
}


