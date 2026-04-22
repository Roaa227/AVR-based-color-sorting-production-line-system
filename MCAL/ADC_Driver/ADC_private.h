/*
 * ADC_private.h
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#ifndef MCAL_ADC_DRIVER_ADC_PRIVATE_H_
#define MCAL_ADC_DRIVER_ADC_PRIVATE_H_

#define ADMUX   (*(volatile u8*)0x27)
#define ADCSRA   (*(volatile u8*)0x26)
#define ADCH   (*(volatile u8*)0x25)
#define ADCL   (*(volatile u16*)0x24)

//ADMUX
#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define MUX4 4
#define ADLAR 5
#define REFS0 6
#define REFS1 7


//ADCSRA
#define ADPS0 0 //Prescaler
#define ADPS1 1 //Prescaler
#define ADPS2 2 //Prescaler
#define ADIE 3
// When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete
//interrupt is activated
#define ADIF 4 //This bit is set when an ADC conversion completes and the Data Registers are updated
#define ADATE 5 //conversion with each trigger (OFF)
#define ADSC 6 //conversion
#define ADEN 7 //enable


//data Reg
//ADCL must be read first, then ADCH





#endif /* MCAL_ADC_DRIVER_ADC_PRIVATE_H_ */
