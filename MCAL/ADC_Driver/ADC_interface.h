/*
 * ADC_interface.h
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */
#ifndef ADC_H_
#define ADC_H_

#include "ADC_private.h"
#include "../../Macros/std_type.h"
#include "../../Macros/BIT_MATH.h"

//5->lm35 2.56->LDR
#define ADC_MAX_VALUE 1023

/* function prototypes */

/* function responsible to init ADC */
void ADC_init(f32 Vref, u8 Prescaler);
/* function responsible to read ADC channel */
u16 ADC_readChannel(u8 channel_num);

#endif /* ADC_H_ */
