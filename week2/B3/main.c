#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

int idx = 0;

ISR( INT0_vect )
{
	if(PIND & 0x02){
		idx= 0;
		}
	else{
		idx++;
	}
	display(idx);
}

ISR( INT1_vect )
{ 
	if(PIND & 0x01){
		idx= 0;
		}
	else{
		idx--;
		}
	display(idx);
}


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

unsigned char Numbers [16] =
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A
	0b11111100, //B
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
	0b01110001, //F
	};


void display(int digit){
	if(digit >= 0 && digit <= 15){
		//inside the range
			PORTB = Numbers[digit];
		}else{
		//outside the range
		//show an E
		PORTB = 0b01111001;
	}
}


int main(){
	DDRB = 0xff;
	DDRD = 0x0;

	EICRA |= 0x0B;		
	EIMSK |= 0x03;

	sei();

	while(1)
	{	// empty     
	}
}