/*
 * ADC_interface.c
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#include "ADC_interface.h"

void ADC_init(f32 Vref, u8 Prescaler){
    // Choose Vref
    if (Vref == 0.0f) {
        CLEAR_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    }
    else if (Vref == 5.0f) {
        SET_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    }
    else if (Vref == 2.56f) {
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
    }

    // ENABLE
    SET_BIT(ADCSRA, ADEN);

    // Prescaler
    switch (Prescaler) {
        case 2:
            CLEAR_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
        case 4:
            CLEAR_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;
        case 8:
            CLEAR_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
        case 16:
            SET_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;
        case 32:
            SET_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
        case 64:
            SET_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;
        case 128:
            SET_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
        default:
            // Invalid prescaler → default to 128
            SET_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
    }

    // ADLAR = 0
    CLEAR_BIT(ADMUX, ADLAR);

    // Interrupt disable
    CLEAR_BIT(ADCSRA, ADIE);
}

u16 ADC_readChannel(u8 channel_num){
	ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);

	SET_BIT(ADCSRA, ADSC);

	while(BIT_IS_CLEAR(ADCSRA, ADIF));

	SET_BIT(ADCSRA, ADIF);

	return ADCL;
}
