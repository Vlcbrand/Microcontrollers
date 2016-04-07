/*
 * week1_B7(2).c
 *
 * Created: 15-2-2016 12:36:40
 * Author : Vincent
 */ 

#include <avr/io.h>

#include <stdio.h>
#include "states.h"
#include <util/delay.h>

typedef void *(*StateFunc)();

int main(){
	
	DDRD = 0b00000000;

	StateFunc func = startstate();

	while (1){
		func = (StateFunc) (*func)();
	}
	return 1;
}

void *s1(){
	PORTD = 0b00000001;
	while(1){
	if(PIND & 0b01000000)
		return startstate();
	else if (PIND & 0b00010000)
		return s2();
		}
}

void *s2(){
	PORTD = 0b00000010;
	while(1){
	if(PIND & 0b00010000)
		return s3();
	else if (PIND & 0b01000000)
		return startstate();
		}
	
}

void *s3(){
	PORTD = 0b00000100;
	while(1){
		if(PIND & 0b00100000)
			return endstate();
		else if (PIND & 0b01000000)
			return startstate();
	}
}

void *endstate(){
	PORTD = 0b00000000;
	while(1){
		if (PIND & 0b01000000)
		return startstate();
	}
}

void *startstate(){
	PORTD = 0b11111111;
	while(1){
		if(PIND & 0b00100000){
			return s1();
			//PORTD = 0b00000010;
		} 
		if(PIND & 0b00010000){
			return s2();
			//PORTD = 0b00000001;
		}

		
		}
}

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
