/*
 * week1_B6.c
 *
 * Created: 2-2-2016 15:34:58
 * Author : Vincent
 */ 
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
    DDRD = 0b11111111;
	DDRC = 0b00000000;

	int pressed = 0;
    int count = 0;

	while (1) 
    {
		count++;
		if(PINC & 0b00000001)
		{
		if(pressed == 1){
			 pressed = 0;
			 
		}else{
		pressed=1;
		}
		count = 0;

		}
	
	
		if(pressed == 0)
		{
			if(count < 1000){
				PORTD = 0b10000000;
			}else{
				PORTD = 0b00000000;
			}

			if(count == 2000){
				count = 0;
			}
				
		}
	 
		if(pressed == 1){
			if(count < 250){
				PORTD = 0b10000000;
			}
			else{
				PORTD = 0b00000000;
			}

			if(count == 500){
			count =0 ;
			}

		}
		
		wait(1);

    }
}

