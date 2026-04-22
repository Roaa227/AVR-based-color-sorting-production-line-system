/*
 * INT_private.h
 *
 *  Created on: Sep 1, 2025
 *      Author: hp
 */

#ifndef MCAL_EXTERNAL_INTERRUPTS_DRIVER_INT_PRIVATE_H_
#define MCAL_EXTERNAL_INTERRUPTS_DRIVER_INT_PRIVATE_H_

#define SREG   (*(volatile u8*)0x5F)
#define MCUCR   (*(volatile u8*)0x55)
#define MCUCSR   (*(volatile u8*)0x54)
#define GICR   (*(volatile u8*)0x5B)
#define GIFR   (*(volatile u8*)0x5A)

#define I_BIT 7

#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define ISC2 6

#define INT1 7
#define INT0 6
#define INT2 5

#define INTF1 7
#define INTF0 6
#define INTF2 5


#endif /* MCAL_EXTERNAL_INTERRUPTS_DRIVER_INT_PRIVATE_H_ */
