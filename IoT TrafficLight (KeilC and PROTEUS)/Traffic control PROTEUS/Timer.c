#include <REG52.H>

sbit LED_BLINK = P1^0; 
unsigned int counter;

void Init_Timer0(void);

void Timer0(void) interrupt 1 using 1
{
	TF0 = 0;
	counter--;
	if(counter == 0)
	{
		counter = 250;
		LED_BLINK = ~LED_BLINK;
	}
	TH0 = 0xDB; 
	TL0 = 0xF2;			
}

void Init_Timer0(void) 
{
	TMOD = 0x01;
	ET0 = 1;
	EA = 1;
	TH0 = 0xDB; 
	TL0 = 0xF2;

	TR0 = 1;
}	  
void main(void)
{
	Init_Timer0(); 	
	counter = 250;
	P1 = 0xFE;

	while(1);
}

