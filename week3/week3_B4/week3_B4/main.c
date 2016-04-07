/*
 * week3_B4.c
 *
 * Created: 8-3-2016 14:33:44
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

/*-----global variables-----*/
int counter;

ISR (TIMER2_COMP_vect) // timer2 overflow interrupt
{
	counter++;
	if(counter == 3){
		PORTD = 0b0000000;
		}else if(counter == 8){
		counter = 0;
		PORTD = 0b1000000;
	}
}

int main(void)
{
	TCCR2 |= (1 << WGM21) | (1 << COM21); // In CTC modus, na het comparen word de timer automatisch gereset
	OCR2 = 157; //Aantal timer ticks (berekend in de calculator), dit word in het compare register gezet. Zodra deze gelijk zijn word de interupt aangeroepen
	TIMSK |= (1 << OCIE2); //Zet de interupt aan op de compere value
	TCCR2 |=    (1 << CS22); // Prescaler word op 256 gezet
	DDRD = 0b1111111;
	PORTD = 0b1000000;
	sei(); // i bit word gezet (is nodig om interupst te activeren)

    while (1) 
    {

    }
	return 1;
}

