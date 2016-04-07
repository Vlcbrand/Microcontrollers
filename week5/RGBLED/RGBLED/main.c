#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	OCR1A = 0;					// RED, default, off
	OCR1B = 0;					// GREEN, default, off
	OCR1C = 0;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}

// Set pulse width for RED on pin PB5, 0=off, 255=max
void setRed( unsigned char red )
{
	OCR1A= red;
}

void setGreen( unsigned char green){
	OCR1B = green;
}
void setBlue( unsigned char blue)
{
	OCR1C = blue;
}

// Main program: Counting on T1
int main( void )
{
	DDRB = 0xFF;					// set PORTB for compare output
	timer1Init();
	wait(100);

	while (1)
	{
		for(int red = 255; red >= 0; red--) {
			for (int blue = 255; blue >= 0; blue--) {
				for (int green  = 255; green >= 0; green--) {
					wait(1);
					setRed(red);
					setBlue(blue);
					setGreen(green);
					
					
				}
			}
			
			
		}
	}
}
