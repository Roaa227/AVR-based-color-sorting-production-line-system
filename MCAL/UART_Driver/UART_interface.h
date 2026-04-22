/*
 *      Author: Mohamed Newir
 *      Created on: Aug 6, 2025
 *      File name: UART.h
 *      Description:
 *      			UART function declaration
 */


#ifndef MCAL_UART_DRIVER_INCLUDE_UART_H_
#define MCAL_UART_DRIVER_INCLUDE_UART_H_

#include "../../Macros/std_type.h"
#include "../../Macros/BIT_MATH.h"
#include "UART_private.h"
/* max length of received string */
#define MAX_STRING_LENGTH 50

/* UART parity mode data type declaration */
typedef enum{
	DISABLED, EVEN_PARITY, ODD_PARITY
}PARITY_MODE_t;

/* UART STop select data type declaration */
typedef enum{
	ONE_BIT, TWO_BIT
}STOP_SELECT_t;

/* UART data type declaration */
typedef struct{
	u32 baudRate;
	Bool_t ASYNC_DSM;
	PARITY_MODE_t mode;
	STOP_SELECT_t select;
}UART_t;

/* UART initialization */
void UART_init(UART_t *uart);

/* UART receive byte */
Bool_t UART_receiveByte(u8 *data);

/* UART send byte */
void UART_sendByte(const u8 data);

/* UART receive string */
void UART_receiveString(u8 *str);

/* UART send string */
void UART_sendString(const u8 *str);



#endif /* MCAL_UART_DRIVER_INCLUDE_UART_H_ */
