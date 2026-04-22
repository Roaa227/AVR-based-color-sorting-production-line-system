/*
 * ServoMotor.h
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */

#ifndef HAL_SERVOMOTOR_SERVOMOTOR_H_
#define HAL_SERVOMOTOR_SERVOMOTOR_H_




#include "../../MCAL/Timers_Driver/Timer0.h"




// تحريك السيرفو لأي زاوية (0 → 180)
void SERVO_voidMove(u8 angle);

// تهيئة السيرفو
void SERVO_init(void);







#endif /* HAL_SERVOMOTOR_SERVOMOTOR_H_ */






