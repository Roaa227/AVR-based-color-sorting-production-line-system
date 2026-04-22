

/* used libraries */
#include "external_eeprom.h"
#include "../../MCAL/TWI_Driver/TWI_interface.h"

/* function write one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_writeByte(u16 u16addr,u8 u8data){

	TWI_start(); /* send start bit */
	/* check TWI status */
	if(TWI_getStatus() != TWI_START){
		return ERROR;
	}

	/* send device address in write mode */
	TWI_writeByte((u8)(0xA0 | ((u16addr & 0x0700)>>7) ));
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}

	/* send memory location */
	TWI_writeByte((u8)(u16addr));
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	/* send data */
	TWI_writeByte(u8data);
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	/*send stop bit*/
	TWI_stop();

	return SUCCESS;
}

/* function read one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_readByte(u16 u16addr,u8 *u8data){

	TWI_start(); /* send start bit */
	/* check TWI status */
	if(TWI_getStatus() != TWI_START){
		return ERROR;
	}

	/* send device address in write mode */
	TWI_writeByte((u8)(0xA0 | ((u16addr & 0x0700) >>7)));
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}

	/* send memory location */
	TWI_writeByte((u8)(u16addr));
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	TWI_start(); /* send repeated start*/
	/* check TWI status */
	if(TWI_getStatus() != TWI_REP_START){
		return ERROR;
	}

	/* send device address in write mode */
	TWI_writeByte((u8)(0xA0 | ((u16addr & 0x0700) >>7) | 1));
	/* check TWI status */
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK){
		return ERROR;
	}

	*u8data = TWI_readByteWithNACK(); /* read data in specified memory location in the EEPROM*/
	/* check TWI status */
	if(TWI_getStatus() != TWI_MR_DATA_NACK){
		return ERROR;
	}
	TWI_stop(); /* send stop bit */

	return SUCCESS;
}
