#include <avr/io.h>

int main( void )
{
	DDRD = 0xFF;
			// set PORTB for compare output
	
	while(1){
	PORTD = 0xFF;	
	}
	return 0;
}