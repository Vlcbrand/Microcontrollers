/*
 * week3_B1.c
 *
 * Created: 29-2-2016 15:45:40
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
 	// Init I/O
	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	// Init LCD
	init_4bits_mode();

	// Write sample string
	lcd_write_string("hoi");

	// Loop forever
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}

	return 1;
}

