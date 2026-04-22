
#ifndef KEYPAD_H_


#include "../../MCAL/DIO_Driver/DIO_interface.h"

#define KEYPAD_H_


/* row/columns number for keypad */
#define KEYPAD_ROW 4
#define KEYPAD_COL 4


/* keypad port/pin configuration */

/* for ROWS */
#define KEYPAD_ROW_PORT_ID PORT_B
#define KEYPAD_FIRST_ROWS_PIN_ID PIN_0
/* for COLS*/
#define KEYPAD_COL_PORT_ID PORT_B
#define KEYPAD_FIRST_COL_PIN_ID PIN_4

/* keypad logic configuration */
#define KEYPAD_BUTTON_PRESSED LOW
#define KEYPAD_BUTTON_RELEASED HIGH

/* function prototype */

/* get the key which is pressed */
u8 KEYPAD_getPressedKey(void);

#endif


