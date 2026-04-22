/*
 * TWI_interface.h
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */

#ifndef MCAL_TWI_DRIVER_TWI_INTERFACE_H_
#define MCAL_TWI_DRIVER_TWI_INTERFACE_H_


#include "../../Macros/std_type.h"
#include "../../Macros/BIT_MATH.h"
#include "TWI_private.h"


//Status
#define TWI_START			0x08 /* confirm start is sent*/
#define TWI_REP_START		0x10 /* confirm repeated start is sent */
#define TWI_MT_SLA_W_ACK	0x18 /* confirm master sent salve address and in write mode */
#define TWI_MT_SLA_R_ACK 	0x40 /* confirm master sent salve address and in read mode */
#define TWI_MT_DATA_ACK     0x28 /* confirm master sent Data and acknowledgment received from slave  */
#define TWI_MR_DATA_ACK		0x50 /* confirm master receive Data and acknowledgment sent by slave */
#define TWI_MR_DATA_NACK 	0x58 /* confirm master sent Data and no acknowledgment sent by slave */




/* Function Prototypes */

/* function initialize I2C in master */
void TWI_init(void);

/* function sent start bit */
void TWI_start(void);

/* function sent stop bit */
void TWI_stop(void);

/* function write byte */
void TWI_writeByte(u8 data);

/* function read byte with acknowledgment */
u8 TWI_readByteWithACK(void);

/* function read byte with no acknowledgment */
u8 TWI_readByteWithNACK(void);

/* function get I2C status */
u8 TWI_getStatus(void);

#endif /* MCAL_TWI_DRIVER_TWI_INTERFACE_H_ */
