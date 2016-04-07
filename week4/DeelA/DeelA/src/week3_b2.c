//
// Created by janco on 23-2-16.
//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"
#include <avr/delay.h>

char str[8];
int counter;

ISR (TIMER2_COMP_vect) // timer2 overflow interrupt
{
	OCR2 = 0;
	counter++;
}

void week3_b2(){
	init();
	_delay_ms(1);
	clear_display();
	_delay_ms(4);

	DDRD = 0b01111111;
	TCCR2 |= (1 << WGM21) | (1 << COM21) ;
	TCCR2 |=  (1 << CS22)  | (1 << CS21)  | (1 << CS20);
	TIMSK |= (1 << OCIE2);
	OCR2 = 1;
	sei();

	while (1)
	{
		sprintf(str, "%d", counter);
		clear_display();
		_delay_ms(4);
		display_text(str);
		_delay_ms(1000);
	}
};