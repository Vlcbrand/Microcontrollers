#include <asf.h>
#include <util/delay.h>

int PATTTERN[] = {
	0b00000001,
	0b00000010,
	0b01000000,
	0b00010000,
    0b00001000,
    0b00000100,
    0b01000000,
    0b00100000,    
};

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
    }
}

int main (void)
{
	board_init();

	DDRD = 0b11111111; //PORTD output (7seg display is connected to PORD)
	
	//infite loop
	while(1){
    
		//circle with bitshifts (test)
		/*
			for(int i = 0; i < 6; i++){
				PORTD = 0b0 | (1<<i);
				wait(1000);
			}
      */          
    
		//pattern
    
		for(int i = 0; i < (sizeof(PATTTERN)/sizeof(int)); i++){
			PORTD = PATTTERN[i]; //draw pattern
			wait(2000); //1 sec
		}      
	}
}
