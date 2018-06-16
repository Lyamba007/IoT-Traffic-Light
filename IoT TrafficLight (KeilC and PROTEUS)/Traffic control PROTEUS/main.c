#include<reg52.h> 

sbit KEY=P3^3; 
sbit LED_RED=P1^0; 
sbit LED_YELLOW=P1^1; 
sbit LED_GREEN=P1^2; 
sbit LED_BLUE=P1^3; 


#define BLUE   3
#define GREEN  2
#define YELLOW 1
#define RED	   0

void Init_Timer0(void);
void Timer0_isr(void);

void Delay (unsigned int t)
{  	
	while (--t);
}


void main (void)
{
unsigned char state = RED;

	while (1)        
	  {
	 	switch(state)
		{
			case RED:					 	
				LED_RED = 0;
		 		LED_YELLOW = 1;
				LED_GREEN = 1;
				LED_BLUE = 1;
				Delay (300);
				state = YELLOW;
				break; 
			case YELLOW:
				LED_RED = 1;
		 		LED_YELLOW = 0;
				LED_GREEN = 1;
				LED_BLUE = 1;
				Delay (300);
				state = GREEN;
				break; 
			case GREEN:
				LED_RED = 1;
		 		LED_YELLOW = 1;
				LED_GREEN = 0;
				LED_BLUE = 1;
				Delay (300);
				state = BLUE;
				break; 
			case BLUE:
				LED_RED = 1;
		 		LED_YELLOW = 1;
				LED_GREEN = 1;
				LED_BLUE = 0;
				Delay (300);
				state = RED;
				break; 
			default:
				break;
		 }
	  }
}

void Init_Timer0(void)
{
 TMOD |= 0x01;	  
 EA=1;           
 ET0=1;          
 TR0=1;          
}

void Timer0_isr(void) interrupt 1 using 1
{
 TH0=(65536-500)/256;		
 TL0=(65536-500)*256;      //1ms Square Wave  
                              

 OUT=~OUT;       
 
}