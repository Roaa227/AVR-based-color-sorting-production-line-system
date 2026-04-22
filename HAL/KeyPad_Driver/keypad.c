/*
 * keypad.c
 *
 *  Created on: Aug 28, 2025
 *      Author: hp
 */
#include "keypad.h"
#include <util/delay.h>

static u8 buttons[KEYPAD_ROW][KEYPAD_COL] = {
    { 1, 2, 3, 'A' },
    { 4, 5, 6, 'B' },
    { 7, 8, 9, 'C' },
    { '*', 0, '#', 'D' }
};

u8 KEYPAD_getPressedKey(void){
    u8 row, col;



    DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+1, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+2, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+3, PIN_INPUT);


    DIO_voidSetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
    DIO_voidSetPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);


     DIO_voidSetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, HIGH);
     DIO_voidSetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, HIGH);
     DIO_voidSetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, HIGH);
     DIO_voidSetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, HIGH);

    while(1){
        for(row = 0; row < KEYPAD_ROW; row++){

            DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+row, PIN_OUTPUT);
            DIO_voidSetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+row, KEYPAD_BUTTON_PRESSED);


            _delay_ms(2);


            for(col = 0; col < KEYPAD_COL; col++){
                if (DIO_u8GetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED) {

                    DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+row, PIN_INPUT);
                    return buttons[row][col];
                }
            }


            DIO_voidSetPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID+row, PIN_INPUT);
        }

        _delay_ms(10);
    }
}
