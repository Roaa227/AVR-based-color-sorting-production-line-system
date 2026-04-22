/*
 *  File Name: lcd.ch
 *
 *  Created on: Sep 28, 2024
 *  Author: Mohamed Newir
 *  Description: LCD driver header file
 */

#ifndef LCD_H_
#define LCD_H_
#include "../../MCAL/DIO_Driver/DIO_interface.h"

#define LCD_DATA_BITS_MODE 4
/* LCD PORTS/PINS ID*/
#define LCD_RS_PORT_ID PORT_D
#define LCD_RS_PIN_ID PIN_4

#define LCD_E_PORT_ID PORT_D
#define LCD_E_PIN_ID PIN_5

#define LCD_DATA_PORT PORT_C

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID	PIN_4
#define LCD_DB5_PIN_ID  PIN_5
#define LCD_DB6_PIN_ID  PIN_6
#define LCD_DB7_PIN_ID	PIN_7

#endif

/* LCD COMMANDS */
#define LCD_CLEAR_COMMAND 0x01
#define LCD_GO_TO_HOME 0x02
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_BLINKING 0x0F
#define LCD_SET_CURSOR_LOCATION 0x80
#define LCD_TWO_LINES_8_BITS_MODE 0x38
#define LCD_TWO_LINES_4_BITS_MODE 0x28

#define LCD_TWO_LINES_4_BITS_MODE_INT1 0x33
#define LCD_TWO_LINES_4_BITS_MODE_INT2 0x32

/* lcd function prototypes */

/*
 * function purpose is to initialize LCD: pin direction
 *  , setup lcd data mode 4-bits or 8-bits
 */
void LCD_init(void);

/*
 * function purpose is to send commands to LCD
 */
void LCD_sendCommand(u8 command);

/*
 * function purpose is to display single char on LCD
 */
void LCD_displayChar(u8 character);

/*
 * function purpose is to display strings on LCD
 */
void LCD_displayString(const u8 *str);

/*
 * function purpose is to move cursor to specfic location
 * on screen
 */
void LCD_moveCursor(u8 row,u8 col);

/*
 * function purpose is to display strings on LCD specific row/column
 */
void LCD_displayStringRowColumn(u8 row,u8 col,const u8 *str);

/*
 * function purpose is to display integers on screen
 */
void LCD_integerToString(u16 data);

void LCD_LongIntegerToString(u32 data);

/*
 * function purpose is send command to clear screen
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
