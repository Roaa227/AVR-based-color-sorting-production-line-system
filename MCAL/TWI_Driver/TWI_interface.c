/*
 * TWI_interface.c
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */

#include "TWI_interface.h"

void TWI_init(void){
	//SPEED
	TWBR = 0x02;

	//ENABLE
	SET_BIT(TWCR, TWEN);

	//PRE = 1
	CLEAR_BIT(TWSR, TWPS1);
	CLEAR_BIT(TWSR, TWPS0);

	//ADDRESS (1)
	TWAR = 0x02;
}


void TWI_start(void){
	SET_BIT(TWCR, TWSTA);
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);


	while(BIT_IS_CLEAR(TWCR, TWINT));
}


void TWI_stop(void){
	SET_BIT(TWCR, TWSTO);
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);
}


void TWI_writeByte(u8 data){
	TWDR = data;

	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);
	while(BIT_IS_CLEAR(TWCR, TWINT));
}


u8 TWI_readByteWithACK(void){
	SET_BIT(TWCR, TWEA);
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);

	while(BIT_IS_CLEAR(TWCR, TWINT));

	return TWDR;
}


u8 TWI_readByteWithNACK(void){
	SET_BIT(TWCR, TWINT);
	SET_BIT(TWCR, TWEN);

	while(BIT_IS_CLEAR(TWCR, TWINT));

	return TWDR;
}


u8 TWI_getStatus(void){
	u8 status = TWSR & 0xF8;

	return status;
}


