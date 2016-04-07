/*
 * Week_1_B2.c
 *
 * Created: 2-2-2016 14:03:39
 * Author : Vincent
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0b11111111;
	
	
    while (1) 
    {
		if (PINC & 0b00000001) // Lees knop 0b00000001 uit op rij C
		{
			 PORTD = 0b10000000; // zet PORTD7 op hoog
		}
		else 
		PORTD = 0b00000000;		// zet PORTD7 op laag
    }
	return 1;
}

