#ifndef MCAL_SPI_DRIVER_INCLUDE_SPI_H_
#define MCAL_SPI_DRIVER_INCLUDE_SPI_H_

#include "../../Macros/std_type.h"
#include "../DIO_Driver/DIO_interface.h"
#include "SPI_private.h"

#define SPI_DEFAULT_VALUE 0xFF

#define MAX_STRING_LENGTH 50

/* set SPI speed mode */
#define SPI_DOUBLE_SPEED_MODE F

/* SPI clock rate data type declaration */
typedef enum{
	CLOCK_2 , CLOCK_4, CLOCK_8, CLOCK_16,
	CLOCK_32, CLOCK_64, CLOCK_128
}SPI_CLOCK_RATE;

/* initialize SPI in master mode */
void SPI_masterInit(SPI_CLOCK_RATE clock);

/* initialize SPI in slave mode */
void SPI_slaveInit(void);

/* send receive byte in normal mode */
u8 SPI_sendReceiveByte(u8 data);

/* send receive byte in Daisy mode */
u8 SPI_sendReceiveByteDaisy(void);

/* send send String in normal mode */
void SPI_sendString(u8 *str);

/* send receive String in normal mode */
void SPI_receiveString(u8 *str);

#endif /* MCAL_SPI_DRIVER_INCLUDE_SPI_H_ */
