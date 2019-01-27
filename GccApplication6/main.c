/*
Ошибки:
Error		'TCCR0' undeclared (first use in this function)	GccApplication6	C:\Users\nhac3\Documents\Atmel Studio\7.0\GccApplication6\GccApplication6\main.c	54
Error		'TIMSK' undeclared (first use in this function)	GccApplication6	C:\Users\nhac3\Documents\Atmel Studio\7.0\GccApplication6\GccApplication6\main.c	57
Error		recipe for target 'main.o' failed	GccApplication6	C:\Users\nhac3\Documents\Atmel Studio\7.0\GccApplication6\GccApplication6\Debug\Makefile	76
*/
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char Data_Num_1, Data_Num_2, Data_Num_3, Data_Num_4, Data;
unsigned char digits[10] = {16,115,36,33,67,129,128,51,0,1};

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
		PORTB |= (1<<0);
		PORTB &=~ (1<<3);
		break;
		case 2:
		PORTD = digits [ Data_Num_2 ];
		PORTB |= (1<<1);
		PORTB &=~ (1<<0);
		break;
		case 3:
		PORTD = digits [ Data_Num_3 ];
		PORTB |= (1<<2);
		PORTB &=~ (1<<1);
		break;
		case 4:
		PORTD = digits [ Data_Num_4 ];
		PORTB |= (1<<3);
		PORTB &=~ (1<<2);
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
	TCCR0 &= (1<<6);
	TCCR0 |= (1<<3);
	TCCR0 |= (1<<1);
	TIMSK |= (1<<1);
	//==================//
	DDRD  = 255;
	PORTD = 255;
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

