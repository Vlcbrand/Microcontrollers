/*
 * Week1_b4.c
 *
 * Created: 2-2-2016 14:47:14
 * Author : Vincent
 */ 

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );	
	}
}

int main(void)
{
    /* Replace with your application code */
   DDRD = 0b11111111;
   int light = 0b00000001;
   
    while (1) 
    {
		for(int x=0; x<7; x++)// de for-loop die de lichtjes laat aflopen.
			wait( 500 );
			PORTD = light;		
			light = light<<1;
		}
		
		for (int x=0; x<7; x++){// de for-loop die de lichtjes laat oplopen,
			wait( 500 );		//die gebeurt als het laatste lichtje onderaan aan is.
			PORTD = light;
			light = light>>1;
		}
		

    }
	return 1;
}


