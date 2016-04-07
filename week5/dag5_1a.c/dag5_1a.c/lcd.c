#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

/*-----functions-----*/
void e_high_low();
void lcd_write_data(unsigned char dat);
void lcd_write_char(unsigned char dat);
void display_4_bit();

/*
	PORTC only uses the first 4 bits, that's why the PORTC values end with 0s, example:
	DISPLAY settings
	PORTC = 0x00; -> first it sends 0 (only the first 4 bits)
	e_high_low(); -> set it
	PORTC = 0xF0; -> F = 1111 this means according to the datasheet (first 1 used to let the LCD know I want to do stuff with the display)
					 second 1 (1 = display on, 0 = display off)
					 third 1 (1 = cursor on, 0 = cursor off)
					 fourth  1 (1 = blink on, 0 = blink off)
*/
void init(){
	//4 bit modus
	DDRC = 0xFF;

	//all low
	PORTC = 0x00;

	//4bit modus
	PORTC = 0x20;
	e_high_low();
	
	//2 lines
	lcd_write_data(0x28);
	
	//display on/off
	lcd_write_data(0x0F);
	
	//entry mode set (increase cursor)
	lcd_write_data(0x06);

	//ddram home
	lcd_write_data(0x02);
}

void display_4_bit(){
	//PORTC output
	DDRC = 0xFF;

	//all low
	PORTC = 0x00;

	//4bit modus
	PORTC = 0x20;
	e_high_low();
}

void display_text(char *str){
	while(*str){
		lcd_write_char(*str++);
	}
}

void display_int(int val){
	char c[100];
	itoa(val, c, 10);
	display_text(c);
}

void set_cursor(int position){
	if(position > 0){
		//right
		for(int i = 0; i < position; i++){
			lcd_write_data(0b00010100);
		}
	}else{
		//left
		for(int i = position; i < 0; i++){
			lcd_write_data(0b00010000);
		}
	}
}

/*-----raw lcd functions-----*/
void lcd_write_data(unsigned char dat){
	PORTC = dat;//will use the first 4 bits
	e_high_low();
	PORTC = (dat << 4); //shift the bits 4 to the left (first 4 will be replaced with the last 4)
	e_high_low();
}

void ddram_home(){
	lcd_write_data(0x02);
}

void lcd_write_char(unsigned char dat)
{
	//first 4 bits
	PORTC = dat;
	PORTC |= (1<<2);
	e_high_low();
	
	//last 4 bits
	PORTC = (dat<<4);
	PORTC |= (1<<2);
	e_high_low();
}

/*
set the E pin High and then Low
*/
void e_high_low(){
	PORTC |= (1<<3);
	_delay_ms(1);
	PORTC &= ~(1<<3);
	_delay_ms(1);
}

/*
shift all characters 1 to the right
*/
void lcd_shift_characters_right(){
	lcd_write_data(0x1C);
}

void clear_display(){
	lcd_write_data(0x01);
}