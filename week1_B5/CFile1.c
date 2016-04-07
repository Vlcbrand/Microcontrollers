/*
 * week1_B5.c
 *
 * Created: 2-2-2016 15:15:37
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		
	}
}

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x08, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};



int main(void)
{
    DDRD = 0b11111111;

    while (1) 
    {
		int index = 0;
		/*
		while( pattern[index].delay != 0 ) { // loopt de array af en zet het lampje aan die gelinkt is aan de .data van de array.
			PORTD = pattern[index].data;
			wait(pattern[index].delay+1000); // wacht de correcte tijd die in de .delay staat van in de array.
			index++;
		}*/
		PORTD=0b11111111;
    }
	return 0;
}


