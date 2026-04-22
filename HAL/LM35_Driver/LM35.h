/*
 * LM35.h
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#ifndef HAL_LM35_DRIVER_LM35_H_
#define HAL_LM35_DRIVER_LM35_H_
#include "../../MCAL/ADC_Driver/ADC_interface.h"


#define LM35_MAX_VOLTAGE 1.5
#define LM35_MAX_TEMP    150.0

u8 READ_LM35(u8 channel_num);



#endif /* HAL_LM35_DRIVER_LM35_H_ */
