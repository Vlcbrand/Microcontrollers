#include <avr/io.h>
#include <util/delay.h>


/******************************************************************/
void twi_init(void)

{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

/******************************************************************/
void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

/******************************************************************/
void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04);
}

/******************************************************************/
void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

/******************************************************************/
void wait( int ms )

{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

typedef struct {
	unsigned int column;
	unsigned int row ;
} SMILEY_STRUCT;

SMILEY_STRUCT realpattern[] = {
{255,0},{255,2},{255,4},{255,6},{255,8},{255,10},{255,12},{255,14}, // all rows filled
{127,0},{127,2},{255,4},{255,6},{255,8},{255,10},{127,12},{127,14},		// 
{126,0},{127,2}, {254,4}, {254,6}, {254,8}, {254,10},{127,12},{126,14},	//	|
{126,0},{125,2},{252,4},{254,6},{254,8},{252,10},{125,12},{126,14},		//	|	smiley reveals from bottom up
{126,0},{121,2},{252,4},{250,6},{250,8},{252,10},{121,12},{126,14},		//	V
{126,0},{113,2},{244,4},{242,6},{242,8},{244,10},{113,12},{126,14},		//
{126,0},{97,2},{244,4},{226,6},{226,8},{244,10}, {97,12},{126,14},		//	
{94,0},{97,2},{212,4},{194,6},{194,8},{212,10},{97,12},{94,14},			//
{30,0},{33,2},{212,4},{194,6},{194,8},{212,10},{33,12},{30,14}};


void twi_clear(void){
	int i = 0x00;
	for(; i <=0x0E; i += 0x02){
		twi_start();
		twi_tx(0xE0);
		twi_tx(i);
		twi_tx(0x00);
		twi_stop();
	}
}

void write_data(int row, int column){
	twi_start();
	twi_tx(0xE0);		// Display I2C address + R/W bit
	twi_tx(row);	// Address
	twi_tx(column);  //column
	twi_stop();
}

void play_fill_animation(){
	int del = 250;

	int start_val = 64;
	int last_val = 64;

	for(int i =  0; i < 8; i+=2){
		//links naar rechts
		for(int i = 0; i < 8; i++){
			write_data(i*2, start_val);
			wait(del);
		}

		if(start_val == 127){
			start_val+=128;	
		}else{
			last_val = last_val/2;
			start_val += (last_val);
		}

		//inverse
		for(int i = 8; i >= 0; i--){
			write_data(i*2, start_val);
			wait(del);
		}
		last_val = last_val/2;
		start_val += (last_val);
	}
	wait(3500);
}

void clear_rows(){
	int start_val = 127;
	int counter_val = 1;

		for(int x = 0; x < 72; x++){			
			write_data(realpattern[x].row, realpattern[x].column);
			wait(250);
		}
	}


/******************************************************************/
int main( void )
 
{
	
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();

	twi_clear();

		play_fill_animation();
		clear_rows();
	
	return 1;
	}
