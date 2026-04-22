/*
 * UART_private.h
 *
 *  Created on: Sep 9, 2025
 *      Author: hp
 */

#ifndef MCAL_UART_DRIVER_UART_PRIVATE_H_
#define MCAL_UART_DRIVER_UART_PRIVATE_H_

#define UDR   (*(volatile u8*)0x2C)
#define UCSRA   (*(volatile u8*)0x2B)
#define UCSRB   (*(volatile u8*)0x2A)
#define UBRRL   (*(volatile u8*)0x29)
#define UBRRH   (*(volatile u8*)0x40)
#define UCSRC   (*(volatile u8*)0x40)


#define RXC     7   // USART Receive Complete
#define TXC     6   // USART Transmit Complete
#define UDRE    5   // USART Data Register Empty
#define FE      4   // Frame Error
#define DOR     3   // Data OverRun
#define PE      2   // Parity Error
#define U2X     1   // Double the Transmission Speed
#define MPCM    0


#define RXCIE   7   // RX Complete Interrupt Enable
#define TXCIE   6   // TX Complete Interrupt Enable
#define UDRIE   5   // USART Data Register Empty Interrupt Enable
#define RXEN    4   // Receiver Enable
#define TXEN    3   // Transmitter Enable
#define UCSZ2   2
#define RXB8    1
#define TXB8    0


#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0


#endif /* MCAL_UART_DRIVER_UART_PRIVATE_H_ */
