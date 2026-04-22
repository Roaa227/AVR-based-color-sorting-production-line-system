/*
 * UART_interface.c
 *
 *  Created on: Sep 9, 2025
 *      Author: hp
 */


#include "UART_interface.h"


void UART_init(UART_t *uart){
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, TXEN);


//	SET_BIT(UCSRC, URSEL);

	u8 usrc = (1 << URSEL);
	switch(uart->ASYNC_DSM){
	case T:
		CLEAR_BIT(usrc, UMSEL);
		break;
	case F:
		SET_BIT(usrc, UMSEL);
		break;
	}


	switch(uart->mode){
	case DISABLED:
		CLEAR_BIT(usrc, UPM0);
		CLEAR_BIT(usrc, UPM1);
		break;
	case EVEN_PARITY:
		CLEAR_BIT(usrc, UPM0);
		SET_BIT(usrc, UPM1);
		break;
	case ODD_PARITY:
		SET_BIT(usrc, UPM0);
		SET_BIT(usrc, UPM1);
		break;
	}


	switch(uart->select){
	case ONE_BIT:
		CLEAR_BIT(usrc, USBS);
		break;
	case TWO_BIT:
		SET_BIT(usrc, USBS);
		break;
	}

	SET_BIT(usrc, UCSZ0);
	SET_BIT(usrc, UCSZ1);
	CLEAR_BIT(usrc, UCSZ2);

	UCSRC = usrc;

	UBRRL = uart->baudRate;
	UBRRH = uart->baudRate >> 8;
}


Bool_t UART_receiveByte(u8 *data){
	while(BIT_IS_CLEAR(UCSRA, RXC));

	*data = UDR;

	if(data != NULL_PTR){
		return T;
	}else{
		return F;
	}

}


void UART_sendByte(const u8 data){
	while(BIT_IS_CLEAR(UCSRA, UDRE));

	UDR = data;
}


void UART_receiveString(u8 *str){
	u8 i = 0;
	u8 data;
	while(UART_receiveByte(&data) != '#'){
		str[i] = data;
		i++;
	}

//	i++;
	str[i] = '\0';
}


void UART_sendString(const u8 *str){
	u8 i = 0;

	while(str[i] != '\0'){
		UART_sendByte(str[i]);
		i++;
	}
}



