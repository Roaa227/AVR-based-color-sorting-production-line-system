/*
 * ServoMotor.c
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */

#include "ServoMotor.h"


#define SERVO_CENTER 90   // الوضع الأساسي (النص)


void SERVO_voidMove(u8 angle) {
    if (angle > 180) angle = 180;   // حماية من القيم الغلط

    // تحويل الزاوية إلى duty cycle بين 5% و 10%
//    u8 duty = ((angle * 5) / 180) + 5;
    u8 duty = 13 + ((u16)angle * 13) / 180;


    // ضبط قيمة ال PWM في Timer0
    TIMER0_FAST_PWM_set_dutyCycle(duty);
}


// تهيئة السيرفو
void SERVO_init(void) {
    // إعداد Timer0 على Fast PWM - Non Inverting - Prescaler 64
	TIMER0_FAST_PWM_init(NON_INVERTING_MODE, PRE_256);
    // أول ما يبدأ السيرفو يبقى في النص
    SERVO_voidMove(SERVO_CENTER);
}

