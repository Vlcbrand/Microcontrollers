

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

/*-----functions-----*/
void test_display();

/*-----global variables-----*/
int counter;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

ISR (TIMER2_COMP_vect)
{
	OCR2 = 0;  //reset the OCR2 value (more responsive button)
	counter++; //increment the counter
	
	ddram_home(); //overwrite old data
	display_int(counter); //display the old data
}

int main( void )
{
	//lcd init
	init();
	display_int(counter); //display 0

	TCCR2 |= (1 << WGM21) | (1 << COM21) ; //WGM21 -> CTC(clear timer on compare) mode, COM21 -> Clear OC2 on compare match
	TCCR2 |=  (1 << CS22)  | (1 << CS21)  | (1 << CS20); //set the clock to external clock source on pin T2 rising edge.
	TIMSK |= (1 << OCIE2); //enable counter2 output compare match interrupt
	OCR2 = 1; //this is the value which gets compared to 
	sei();

	while (1)
	{
		//infinite loop
	}
	return 1;
}

void test_display(){
	init();
	display_text("test text");
	set_cursor(3);
}