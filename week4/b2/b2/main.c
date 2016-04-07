#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

uint16_t analogvalue;
char str[100];

int main(){
	init();
	//ALLES IN DATAHSEET OP PAGINA 245
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // prescaler op  64 - 125KHz op 8mhz
	ADMUX |= (1 << REFS0) | (1 << REFS1); // analoog signaal word nu vergeleken met de interne voltage reference (dus deze is als het goed is 2.56 volt)
	ADMUX |= (1 << ADLAR); // 8 bit gegevens
	ADMUX |= (1 << MUX0) | (1 << MUX1); // op pf3 zetten
	ADCSRA |= (1 << ADEN);  // adc aanzetten
	DDRA = 0xff;
	DDRB = 0xff;
	while(1)
	{
		ADCSRA |= (1 << ADSC);  // a2d pollen
		while(ADCSRA & (1 << 6)){ //Wachten tot ADSC 0 word, dan is de data klaar
		}
		//Hierna is het lezen klaar en hebben we de data in de ADCH register staan.
		_delay_ms(500);
		ddram_home();
		sprintf(str, "Waarde:%02d", ADCH);
		display_text(str);
	}
}
