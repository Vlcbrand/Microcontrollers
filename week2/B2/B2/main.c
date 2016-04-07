/*
 * B2.c
 *
 * Created: 8-3-2016 10:59:04
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*-----global variables-----*/
char counter = 0;

ISR(INT1_vect){
	counter++;
	if(counter>8){
		counter=0;		
	}
	PORTB = (1<<counter);	// Bitshift portB so light goes up
}

ISR(INT2_vect){
	if(counter == 0){
		counter = 8;
	} else {
		counter--;
	}
	PORTB = (1<<counter);	// Bitshift portB so light goes down
}

int main(void)
{
	DDRD = 0x00;		// D ports on input
	DDRB = 0xFF;		// B ports on output

	EICRA = 0b00101000;	// INT1 & INT2 falling edge 
	EIMSK = 0b00000110;	// INT1 & INT2 enabled

	sei();				// enable global interrupt system

    while (1) 
    {

    }
}

