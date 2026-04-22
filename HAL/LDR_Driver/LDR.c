/*
 * LDR.c
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#include "LDR.h"

u16 READ_LDR(u8 channel_num){
	u32 ReturnedValue = (u32)ADC_readChannel(channel_num);
	u16 value = (u16)(( ReturnedValue * LDR_MAX_V * 2.56)/(LDR_MAX_VOLTAGE * ADC_MAX_VALUE));
	return value;

}

