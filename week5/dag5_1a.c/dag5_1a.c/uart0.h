/*
 * uart0.h
 *
 * Created: 15-3-2016 11:54:00
 *  Author: Vincent
 */ 


#ifndef UART0_H_
#define UART0_H_

#define CR			0x0d					// ascii code for Carriage Return
#define BIT(x)		(1 << (x))
#define UART0_BAUD	2400					// Baud rate USART0
#define MYUBRR		F_CPU/16/UART0_BAUD - 1	// My USART Baud Rate Register

void usart0_init( void );
void usart0_start( void )	;
int uart0_sendChar( char ch );
char uart0_receiveChar( void );
int uart0_receiveString( char* string);


#endif /* UART0_H_ */