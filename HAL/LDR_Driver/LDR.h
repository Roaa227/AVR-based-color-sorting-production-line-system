/*
 * LDR_interface.h
 *
 *  Created on: Sep 2, 2025
 *      Author: hp
 */

#ifndef HAL_LDR_DRIVER_LDR_H_
#define HAL_LDR_DRIVER_LDR_H_

#include "../../MCAL/ADC_Driver/ADC_interface.h"

#define LDR_MAX_VOLTAGE  2.56
#define LDR_MAX_V    100.0


u16 READ_LDR(u8 channel_num);


#endif /* HAL_LDR_DRIVER_LDR_H_ */
