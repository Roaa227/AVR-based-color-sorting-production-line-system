// ColorSensor.c
#include "ColorSensor.h"
#define F_CPU 8000000UL   // 8 MHz crystal

#define FREQ_SCALING FREQ_20


//Background Detection
u32 background_level;
u32 DETECTION_VTH;

void Background_Color(void);


void TCS3200_Init(void)
{
    // Configure S0–S3 as outputs (on PORTC)
    DIO_voidSetPinDirection(PORT_C, PIN_0, PIN_OUTPUT); // S0
    DIO_voidSetPinDirection(PORT_C, PIN_1, PIN_OUTPUT); // S1
    DIO_voidSetPinDirection(PORT_C, PIN_2, PIN_OUTPUT); // S2
    DIO_voidSetPinDirection(PORT_C, PIN_3, PIN_OUTPUT); // S3

    // OUT pin (PD6) as input
    DIO_voidSetPinDirection(PORT_D, PIN_6, PIN_INPUT);

    // Apply frequency scaling (S0, S1)
    switch(FREQ_SCALING)
    {
        case FREQ_100:
            DIO_voidSetPinValue(PORT_C, PIN_0, HIGH); // S0
            DIO_voidSetPinValue(PORT_C, PIN_1, HIGH); // S1
            break;

        case FREQ_20:
            DIO_voidSetPinValue(PORT_C, PIN_0, HIGH); // S0
            DIO_voidSetPinValue(PORT_C, PIN_1, LOW);  // S1
            break;

        case FREQ_2:
            DIO_voidSetPinValue(PORT_C, PIN_0, LOW);  // S0
            DIO_voidSetPinValue(PORT_C, PIN_1, HIGH); // S1
            break;

        case POWER_DOWN:
            DIO_voidSetPinValue(PORT_C, PIN_0, LOW);
            DIO_voidSetPinValue(PORT_C, PIN_1, LOW);
            break;
    }
}

void TCS3200_SetFilter(u8 filter)
{
    switch(filter)
    {
        case TCS3200_RED:
            DIO_voidSetPinValue(PORT_C, PIN_2, LOW);  // S2
            DIO_voidSetPinValue(PORT_C, PIN_3, LOW);  // S3
            break;

        case TCS3200_BLUE:
            DIO_voidSetPinValue(PORT_C, PIN_2, LOW);
            DIO_voidSetPinValue(PORT_C, PIN_3, HIGH);
            break;

        case TCS3200_GREEN:
            DIO_voidSetPinValue(PORT_C, PIN_2, HIGH);
            DIO_voidSetPinValue(PORT_C, PIN_3, HIGH);
            break;

        default: // CLEAR
            DIO_voidSetPinValue(PORT_C, PIN_2, HIGH);
            DIO_voidSetPinValue(PORT_C, PIN_3, LOW);
            break;
    }
}

u32 TCS3200_ReadFrequency(void)
{
    u16 t1, t2;
    u32 period, freq;

    // Reset Timer1
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // Enable input capture, no prescaler
    TCCR1B = (1<<ICES1) | (1<<CS10);

    // Wait first capture
    SET_BIT(TIFR, ICF1);
    while (BIT_IS_CLEAR(TIFR, ICF1));
    t1 = ICR1;
    SET_BIT(TIFR, ICF1);

    // Wait second capture
    while (BIT_IS_CLEAR(TIFR, ICF1));
    t2 = ICR1;
    SET_BIT(TIFR, ICF1);

    // Compute period
    if (t2 > t1)
        period = t2 - t1;
    else
        period = (0xFFFF - t1) + t2; // overflow

    freq = (u32)F_CPU / period;

    return freq;
}

void TCS3200_GetRGB(u32 *R, u32 *G, u32 *B)
{
    TCS3200_SetFilter(TCS3200_RED);
    *R = TCS3200_ReadFrequency();

    TCS3200_SetFilter(TCS3200_GREEN);
    *G = TCS3200_ReadFrequency();

    TCS3200_SetFilter(TCS3200_BLUE);
    *B = TCS3200_ReadFrequency();
}

u8 IsItemPresent(u32 R, u32 G, u32 B)
{
    u32 total = R + G + B;

    if(total > DETECTION_VTH) {
        return 1;
    } else {
        return 0;
    }
}



u8 Get_Color(u32 *R, u32 *G, u32 *B)
{
    TCS3200_GetRGB(R, G, B);
    u32 total = *R + *G + *B;

    // Step 1: detect if there is an item
    if(total <= DETECTION_VTH) {
        return NOTHING;
    }

    // Step 2: decide color
    if((*R > *G) && (*R > *B)) return RED_t;
    else if((*G > *R) && (*G > *B)) return GREEN_t;
    else if((*B > *R) && (*B > *G)) return BLUE_t;

    return NOTHING;
}


void Background_Color(void){
	u32 R_bg, G_bg, B_bg;

	TCS3200_GetRGB(&R_bg, &G_bg, &B_bg);
	background_level = R_bg + G_bg + B_bg;

	DETECTION_VTH = background_level + 100;
}


