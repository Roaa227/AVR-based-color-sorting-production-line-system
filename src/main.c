/*
 * main.c
 *
 *  Created on: Sep 16, 2025
 *      Author: Roaa
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* ==== MACROS ==== */
#include "../Macros/std_type.h"
#include "../Macros/BIT_MATH.h"

/* ==== MCAL ==== */
#include "../MCAL/DIO_Driver/DIO_interface.h"
#include "../MCAL/External_Interrupts_Driver/INT_interface.h"

/* ==== HAL ==== */
#include "../HAL/DcMotor_Driver/DcMotor.h"
#include "../HAL/StepperMotor_Driver/StepperMotor.h"
#include "../HAL/LCD_Driver/lcd.h"
#include "../HAL/ColorSensor_Driver/ColorSensor.h"

/* ==== LED PINS ==== */
#define LED_RUN_PORT   PORT_B
#define LED_RUN_PIN    PIN_1
#define LED_ERR_PORT   PORT_B
#define LED_ERR_PIN    PIN_5

/* ==== Global Counters ==== */
volatile u16 red_count   = 0;
volatile u16 green_count = 0;
volatile u16 blue_count  = 0;

/* ==== System State ==== */
volatile u8 system_paused = 0;

/* ================== ISR Callbacks ================== */
void pause_btn_ISR(void) {
	system_paused = 1;
	MOTOR_Stop();
	DIO_voidSetPinValue(LED_RUN_PORT, LED_RUN_PIN, LOW);
	LCD_clearScreen();
	LCD_displayString("STATE: PAUSED");
	_delay_ms(300);
}

void resume_btn_ISR(void) {
	system_paused = 0;
	MOTOR_Forward();
	LCD_clearScreen();
	LCD_displayString("STATE: RUNNING");
	DIO_voidSetPinValue(LED_RUN_PORT, LED_RUN_PIN, HIGH);
	DIO_voidSetPinValue(LED_ERR_PORT, LED_ERR_PIN, LOW);
	_delay_ms(1000);
}

void stop_btn_ISR(void) {
	MOTOR_Stop();
	LCD_clearScreen();
	LCD_displayString("STATE: STOPPED");
	DIO_voidSetPinValue(LED_ERR_PORT, LED_ERR_PIN, HIGH);
	DIO_voidSetPinValue(LED_RUN_PORT, LED_RUN_PIN, LOW);
	while (1); // lock system
}

/* ================== MAIN ================== */
int main(void)
{
	/* ==== LEDs ==== */
	DIO_voidSetPinDirection(LED_RUN_PORT, LED_RUN_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(LED_ERR_PORT, LED_ERR_PIN, PIN_OUTPUT);
	DIO_voidSetPinValue(LED_RUN_PORT, LED_RUN_PIN, LOW);
	DIO_voidSetPinValue(LED_ERR_PORT, LED_ERR_PIN, LOW);

	/* ==== Init Drivers ==== */
	LCD_init();
	MOTOR_Init();
	TCS3200_Init();

	/* ==== Two Steppers Config ==== */
	Stepper_t stepper_red = {
		.portNum = PORT_A,
		.mask    = 0x0F,
		.delay   = 10,
		.mode    = FULL_STEP,
		.ULN2003A_used = T
	};
	Stepper_t stepper_blue = {
		.portNum = PORT_A,
		.mask    = 0xF0,
		.delay   = 10,
		.mode    = FULL_STEP,
		.ULN2003A_used = T
	};
	STEPPER_init(&stepper_red);
	STEPPER_init(&stepper_blue);

	/* ==== Enable Interrupts ==== */
	EXT_interrupt_GIE_state(ENABLE);
	EXT_INT0_init(ENABLE, FALLING_EDGE);
	EXT_INT1_init(ENABLE, FALLING_EDGE);
	EXT_INT2_init(ENABLE, FALLING_EDGE);
	EXT_int0_set_cb(pause_btn_ISR);
	EXT_int1_set_cb(resume_btn_ISR);
	EXT_int2_set_cb(stop_btn_ISR);

	/* Buttons input + Pull-ups */
	DIO_voidSetPinDirection(PORT_D, PIN_2, PIN_INPUT);
	DIO_voidSetPinDirection(PORT_D, PIN_3, PIN_INPUT);
	DIO_voidSetPinDirection(PORT_B, PIN_2, PIN_INPUT);
	DIO_voidSetPinValue(PORT_D, PIN_2, HIGH);
	DIO_voidSetPinValue(PORT_D, PIN_3, HIGH);
	DIO_voidSetPinValue(PORT_B, PIN_2, HIGH);

	/* ==== Background calibration ==== */
	Background_Color();

	/* ==== Startup ==== */
	LCD_clearScreen();
	LCD_displayString("Sorting System");
	_delay_ms(1000);

	MOTOR_Forward();
	LCD_clearScreen();
	LCD_displayString("STATE: RUNNING");
	DIO_voidSetPinValue(LED_RUN_PORT, LED_RUN_PIN, HIGH);
	_delay_ms(1000);


	/* ==== Sorting Variables ==== */
	u32 R, G, B;
	u8 colorDetected;

	while (1)
	{
		if (!system_paused)
		{
			colorDetected = Get_Color(&R, &G, &B);

			if (colorDetected == RED_t) {
				red_count++;
				/* ==== LCD Update ==== */
				LCD_clearScreen();
				LCD_moveCursor(0, 0);
				LCD_displayString("R:");
				LCD_integerToString((u8*)red_count);
				LCD_displayString(" G:");
				LCD_integerToString((u8*)green_count);

				LCD_moveCursor(1, 0);
				LCD_displayString("B:");
				LCD_integerToString((u8*)blue_count);

				STEPPER_move_angle(&stepper_red, STEPPER_CCW, 180); // open gate
				_delay_ms(300);
				STEPPER_move_angle(&stepper_red, STEPPER_CW, 180); // back to parallel
			}
			else if (colorDetected == BLUE_t) {
				blue_count++;
				/* ==== LCD Update ==== */
				LCD_clearScreen();
				LCD_moveCursor(0, 0);
				LCD_displayString("R:");
				LCD_integerToString((u8*)red_count);
				LCD_displayString(" G:");
				LCD_integerToString((u8*)green_count);

				LCD_moveCursor(1, 0);
				LCD_displayString("B:");
				LCD_integerToString((u8*)blue_count);

				STEPPER_move_angle(&stepper_blue, STEPPER_CCW, 180); // open gate
				_delay_ms(300);
				STEPPER_move_angle(&stepper_blue, STEPPER_CW, 180); // back to parallel
			}
			else if (colorDetected == GREEN_t) {
				green_count++;
				/* ==== LCD Update ==== */
				LCD_clearScreen();
				LCD_moveCursor(0, 0);
				LCD_displayString("R:");
				LCD_integerToString((u8*)red_count);
				LCD_displayString(" G:");
				LCD_integerToString((u8*)green_count);

				LCD_moveCursor(1, 0);
				LCD_displayString("B:");
				LCD_integerToString((u8*)blue_count);

				// let item pass (both gates parallel)
			}

			/* ==== LCD Update ==== */
			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("R:");
			LCD_integerToString((u8*)red_count);
			LCD_displayString(" G:");
			LCD_integerToString((u8*)green_count);

			LCD_moveCursor(1, 0);
			LCD_displayString("B:");
			LCD_integerToString((u8*)blue_count);

			_delay_ms(500);
		}
	}
}
