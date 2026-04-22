/*
 * LDR.c
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#include "LM35.h"

u8 READ_LM35(u8 channel_num){
	u32 ReturnedValue = (u32)ADC_readChannel(channel_num);
	u8 temp =  (u8)(((u32)ReturnedValue * LM35_MAX_TEMP * 5)/(LM35_MAX_VOLTAGE * ADC_MAX_VALUE));
	return temp;
}
