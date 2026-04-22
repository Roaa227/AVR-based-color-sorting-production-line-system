/*
 * lcd.c
 *
 *  Created on: Aug 27, 2025
 *      Author: hp
 */


#include "lcd.h"

#include<util/delay.h>


void LCD_init(void){

	DIO_voidSetPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	_delay_ms(20);

#if (LCD_DATA_BITS_MODE == 4)
	DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB4_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB5_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB6_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB7_PIN_ID, PIN_OUTPUT);

    LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE_INT1);
    LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE_INT2);
    LCD_sendCommand(LCD_TWO_LINES_4_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
	DIO_vSetPortDir(LCD_DATA_PORT, PORT_OUTPUT);


    LCD_sendCommand(LCD_TWO_LINES_8_BITS_MODE);
#endif

    LCD_sendCommand(LCD_CURSOR_OFF);

    LCD_sendCommand(LCD_CLEAR_COMMAND);



}


void LCD_sendCommand(u8 command){
	DIO_voidSetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOW);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4_PIN_ID, GET_BIT(command,4));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5_PIN_ID, GET_BIT(command,5));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6_PIN_ID, GET_BIT(command,6));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7_PIN_ID, GET_BIT(command,7));

	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOW);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, HIGH);
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4_PIN_ID, GET_BIT(command,0));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5_PIN_ID, GET_BIT(command,1));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6_PIN_ID, GET_BIT(command,2));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7_PIN_ID, GET_BIT(command,3));
#elif (LCD_DATA_BITS_MODE == 8)
	DIO_voidSetPortValue(LCD_DATA_PORT,command);

#endif
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOW);
	_delay_ms(1);

}


void LCD_displayChar(u8 character){
	DIO_voidSetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4_PIN_ID, GET_BIT(character,4));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5_PIN_ID, GET_BIT(character,5));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6_PIN_ID, GET_BIT(character,6));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7_PIN_ID, GET_BIT(character,7));


	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOW);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, HIGH);
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4_PIN_ID, GET_BIT(character,0));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5_PIN_ID, GET_BIT(character,1));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6_PIN_ID, GET_BIT(character,2));
	DIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7_PIN_ID, GET_BIT(character,3));

#elif (LCD_DATA_BITS_MODE == 8)
	DIO_voidSetPortValue(LCD_DATA_PORT, character);
	_delay_ms(1);
#endif

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, LOW);
	_delay_ms(1);

}


void LCD_moveCursor(u8 row,u8 col){
	u8 memAddress;

	switch(row){
	case 0:
		memAddress = col; break;
	case 1:
		memAddress = col + 0x40; break;
	}

	LCD_sendCommand(memAddress | LCD_SET_CURSOR_LOCATION);
}



void LCD_displayString(const u8 *str){
	u8 i=0;

	while(str[i] != '\0'){
		LCD_displayChar(str[i]);
		i++;
	}
}


void LCD_displayStringRowColumn(u8 row,u8 col,const u8 *str){
	LCD_moveCursor(row, col);

	LCD_displayString(str);
}


void LCD_integerToString(u16 data){
	u8 buff[16];
	itoa(data, buff, 10);
	LCD_displayString(buff);
}

void LCD_LongIntegerToString(u32 data){
    u8 buff[32];
    sprintf(buff, "%u", data);
    LCD_displayString(buff);
}

void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
	_delay_ms(1);
}
