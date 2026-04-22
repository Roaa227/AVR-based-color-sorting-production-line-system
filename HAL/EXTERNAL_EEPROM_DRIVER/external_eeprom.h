/*
 * 		File Name: external_eeprom.h
 *
 *  	Created on: Oct 30, 2024
 *      Author: Mohamed Newir
 *      File Description: External EEPROM Header File
 */

#ifndef HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_
#define HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_

/* user defined data types library*/
#include "../../Macros/std_type.h"

/* constant definitions */
#define ERROR   0
#define SUCCESS 1

/* Function Prototypes */

/* function write one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_writeByte(u16 u16addr,u8 u8data);

/* function read one 1 byte in specified address in EEPROM using TWI */
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);



#endif /* HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_ */
