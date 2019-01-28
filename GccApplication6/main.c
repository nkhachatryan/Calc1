
#include <avr/io.h>
#include <avr/interrupt.h>
#define _BV(bit)

volatile unsigned char Data_Num_1, Data_Num_2, Data_Num_3, Data_Num_4, Data;
unsigned char digits[10] = {0x10,0x73,0x24,0x21,0x43,0x81,0x80,0x33,0x00,0x01};

//*******************************//
//*******************************//
ISR (TIMER0_COMPA_vect)
{
	static unsigned char Num_count;
	Num_count ++;
	switch (Num_count)
	{
		case 1:
		PORTD = digits [ Data_Num_1 ];
		PORTB |= _BV(PB0);
		PORTB &=~ _BV(PB3);
		break;
		case 2:
		PORTD = digits [ Data_Num_2 ];
		PORTB |= _BV(PB1);
		PORTB &=~ _BV(PB0);
		break;
		case 3:
		PORTD = digits [ Data_Num_3 ];
		PORTB |= _BV(PB2);
		PORTB &=~ _BV(PB1);
		break;
		case 4:
		PORTD = digits [ Data_Num_4 ];
		PORTB |= _BV(PB3);
		PORTB &=~ _BV(PB2);
		Num_count = 0;
		break;
	}
}
//*******************************//
//*******************************//
void recount ( volatile unsigned char Temp )
{
	asm("cli");
	 Data_Num_1 = Temp /1000;
	 Data_Num_2 = (Temp%1000) / 100;
	 Data_Num_3 = (Temp % 100) / 10;
	 Data_Num_4 = Temp % 10;
	asm("sei");
}


int main(void)
{
	TCCR0A &= (1<<6);
	TCCR0A |= (1<<3);
	TCCR0A |= (1<<1);
	TIMSK0 |= (1<<1);
	//==================//
	DDRD  = 0xFF;
	PORTD = 0xFF;
	DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	PORTB &=~ (1<<0); PORTB &=~ (1<<1); PORTB &=~ (1<<2); PORTB &=~ (1<<3);
	//==================//
	Data = 1221;
	asm("sei");
	while(1)
	{
		asm("nop");
		recount(Data);
		asm("nop");
	}
}

