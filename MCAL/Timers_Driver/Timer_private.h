/*
 * Timer_private.h
 *
 *  Created on: Sep 4, 2025
 *      Author: hp
 */

#ifndef MCAL_TIMERS_DRIVER_TIMER_PRIVATE_H_
#define MCAL_TIMERS_DRIVER_TIMER_PRIVATE_H_

#define TCCR0   (*(volatile u8*)0x53)
#define TCNT0   (*(volatile u8*)0x52)
#define TIFR   (*(volatile u8*)0x58)
#define OCR0   (*(volatile u16*)0x5C)


#define TCCR1A   (*(volatile u8*)0x4F)
#define TCCR1B   (*(volatile u8*)0x4E)
#define TCNT1    (*(volatile u16*)0x4C)   // full 16-bit
#define OCR1A    (*(volatile u16*)0x4A)
#define OCR1B    (*(volatile u16*)0x48)
#define ICR1     (*(volatile u16*)0x46)
#define TIMSK    (*(volatile u8*)0x59)
#define TIFR     (*(volatile u8*)0x58)

#define WGM10 0
#define WGM11 1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

#define TOIE1 2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5


#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1 5



#endif /* MCAL_TIMERS_DRIVER_TIMER_PRIVATE_H_ */
