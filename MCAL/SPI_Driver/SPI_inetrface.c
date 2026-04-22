/*
 * SPI_inetrface.c
 *
 *  Created on: Sep 10, 2025
 *      Author: hp
 */
#include "SPI_interface.h"

void SPI_masterInit(SPI_CLOCK_RATE clock){
	DIO_voidSetPinDirection(PORT_B, PIN_4, PIN_OUTPUT); /* Set SS pin as output */
	DIO_voidSetPinDirection(PORT_B, PIN_5, PIN_OUTPUT); /* Set MOSI pin as output */
	DIO_voidSetPinDirection(PORT_B, PIN_6, PIN_INPUT); /* Set MISO pin as input */
	DIO_voidSetPinDirection(PORT_B, PIN_7, PIN_OUTPUT); /* Set SCK pin as output */


//	SET_BIT(SPCR, SPIE);
	SET_BIT(SPCR, SPE);

	SET_BIT(SPCR, MSTR);


	//MSB first / RISING is the leading edge / sample(receive)
	CLEAR_BIT(SPCR, DORD);
	CLEAR_BIT(SPCR, CPOL);
	CLEAR_BIT(SPCR, CPHA);


	if(SPI_DOUBLE_SPEED_MODE == 0){
		switch(clock){
		case CLOCK_4:
			CLEAR_BIT(SPCR, SPR0);
			CLEAR_BIT(SPCR, SPR1);
			CLEAR_BIT(SPSR, SPI2X);
			break;
		case CLOCK_16:
			SET_BIT(SPCR, SPR0);
			CLEAR_BIT(SPCR, SPR1);
			CLEAR_BIT(SPSR, SPI2X);
			break;
		case CLOCK_64:
			CLEAR_BIT(SPCR, SPR0);
			SET_BIT(SPCR, SPR1);
			CLEAR_BIT(SPSR, SPI2X);
			break;
		case CLOCK_128:
			SET_BIT(SPCR, SPR0);
			SET_BIT(SPCR, SPR1);
			CLEAR_BIT(SPSR, SPI2X);
			break;
		}
	} else{
		switch(clock){
		case CLOCK_2:
			CLEAR_BIT(SPCR, SPR0);
			CLEAR_BIT(SPCR, SPR1);
			SET_BIT(SPSR, SPI2X);
			break;
		case CLOCK_8:
			SET_BIT(SPCR, SPR0);
			CLEAR_BIT(SPCR, SPR1);
			SET_BIT(SPSR, SPI2X);
			break;
		case CLOCK_32:
			CLEAR_BIT(SPCR, SPR0);
			SET_BIT(SPCR, SPR1);
			SET_BIT(SPSR, SPI2X);
			break;
		case CLOCK_64:
			SET_BIT(SPCR, SPR0);
			SET_BIT(SPCR, SPR1);
			SET_BIT(SPSR, SPI2X);
			break;
		}
	}

}


void SPI_slaveInit(void){
	DIO_voidSetPinDirection(PORT_B, PIN_4, PIN_INPUT); /* Set SS pin as input */
	DIO_voidSetPinDirection(PORT_B, PIN_5, PIN_INPUT); /* Set MOSI pin as input */
	DIO_voidSetPinDirection(PORT_B, PIN_6, PIN_OUTPUT); /* Set MISO pin as output */
	DIO_voidSetPinDirection(PORT_B, PIN_7, PIN_INPUT); /* Set SCK pin as input */



//	CLEAR_BIT(SPCR, MSTR);
//	SET_BIT(SPCR, SPE);
	SPCR = (1 << SPE);
}


u8 SPI_sendReceiveByte(u8 data){
	SPDR = data;

	while(BIT_IS_CLEAR(SPSR, SPIF));

	return SPDR;
}


//u8 SPI_sendReceiveByteDaisy(void){
//
//}


void SPI_sendString(u8 *str){
	u8 i = 0;
	while(str[i] != '\0' && i <= MAX_STRING_LENGTH){
		SPI_sendReceiveByte(str[i]);
		i++;
	}

	SPI_sendReceiveByte('#');
}


void SPI_receiveString(u8 *str){
	u8 i=0;

	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_VALUE);

	while(str[i] != '#'){
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_VALUE);
	}

	str[i] = '\0';
}

