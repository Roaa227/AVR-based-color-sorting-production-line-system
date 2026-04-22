/*
 * ColorSensor.h
 *
 *  Created on: Sep 11, 2025
 *      Author: hp
 */

#ifndef HAL_COLORSENSOR_DRIVER_COLORSENSOR_H_
#define HAL_COLORSENSOR_DRIVER_COLORSENSOR_H_

#include "../../Macros/std_type.h"
#include "../../Macros/BIT_MATH.h"
#include "../../MCAL/DIO_Driver/DIO_interface.h"
#include "../../MCAL/Timers_Driver/Timer1.h"

/* Colour filter selection */
#define TCS3200_RED      0
#define TCS3200_GREEN    1
#define TCS3200_BLUE     2
#define TCS3200_CLEAR    3

/* Frequency-scaling selection */
#define FREQ_100   0
#define FREQ_20    1
#define FREQ_2     2
#define POWER_DOWN 3

/* Decoded colour result */
typedef enum {
    RED_t,
    BLUE_t,
    GREEN_t,
    NOTHING
} COLOR_t;

/* ---------- public API (unchanged) ---------- */
void TCS3200_Init(void);

void TCS3200_SetFilter(u8 filter);

u32 TCS3200_ReadFrequency(void);   /* returns frequency in Hz */

void TCS3200_GetRGB(u32 *R, u32 *G, u32 *B);

u8  IsItemPresent(u32 R, u32 G, u32 B);

u8  Get_Color(u32 *R, u32 *G, u32 *B);

/* Optional background calibration */
void Background_Color(void);
extern u32 DETECTION_VTH;

#endif /* HAL_COLORSENSOR_DRIVER_COLORSENSOR_H_ */
