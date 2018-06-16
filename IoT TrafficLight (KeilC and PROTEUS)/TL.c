#include<reg52.h> 			
#include<delay51.h>

sbit BUTTON_ON =P3^2;
sbit BUTTON_ST =P3^3;
sbit BUTTON_GW = P1^7;
 
sbit LED_RED=P1^0; 
sbit LED_YELLOW=P1^1; 
sbit LED_GREEN=P1^2; 


#define YELLOWBLINK 1
#define YELLOWUP 2
#define RED	3
#define YELLOWDOWN 4
#define GREEN  5
#define GREENWAVE 6

#define T1 1000
#define T2 5000
#define T3 T2*3

unsigned char state = YELLOWBLINK;
unsigned char nextState;

bit unPushed = 0;

void StateTransition();
void delay_us(unsigned int uSeconds);
void delay_ms(unsigned int mSeconds);


void delay_us(unsigned int uSeconds)
{
	uSeconds = 0xFFFF - uSeconds; 
	TMOD |= 0x10;    
	TL1 = uSeconds;     
	TH1 = uSeconds>>8;	
	TR1 = 1;		
	while (TF1==0);	
	TR1 = 0;		
	TF1 = 0;	
}


void delay_ms(unsigned int mSeconds)
{
	while (mSeconds--)
	{
		delay_us(1000);
	}
	
	state = nextState;
}


void main (void)
{	
	while(1)
	{
		StateTransition();
	}
}


void StateTransition()  
{ 
	switch(state)
	{
		case YELLOWBLINK:
					 
			if(BUTTON_ON == 0)
			{
				nextState = YELLOWUP;									
			}
						
			else 
			{
				nextState = YELLOWBLINK;
			}
						
			break;
											
		case YELLOWUP:
							
			if(BUTTON_ST == 1 || BUTTON_ON == 1)
			{
				nextState = YELLOWBLINK;
			}
							
			else if (BUTTON_ST == 0)
			{
				nextState = RED;
			}	

			if (BUTTON_GW == 1)
			{
				unPushed = 0;
			}
							
			break;
							
		case RED:

			if(BUTTON_ST == 1 || BUTTON_ON == 1)
			{
				nextState = YELLOWBLINK;
			}
							
			else if (BUTTON_ST == 0)
			{
				nextState = YELLOWDOWN;
			}	
							
			break;
					
		case YELLOWDOWN:

			if(BUTTON_ST == 1 || BUTTON_ON == 1)
			{
				nextState = YELLOWBLINK;
			}
							
			else if (BUTTON_ST == 0)
			{
				nextState = GREEN;
			}	
							
			if (BUTTON_GW == 0 && unPushed == 0)
			{
				nextState = GREENWAVE;
			}
							
			break;
					
		case GREEN:

			if(BUTTON_ST == 1 || BUTTON_ON == 1)
			{
				nextState = YELLOWBLINK;
			}
							
			else if (BUTTON_ST == 0)
			{
				nextState = YELLOWUP;
			}	
							
			break;
		
		case GREENWAVE:
	
			unPushed = 1;
			nextState = YELLOWUP;
							
			break;

						
		default:
			nextState = YELLOWBLINK;
			break;
	}
	
	switch(state)
	{	
		case RED:	
			LED_RED = 0;
			LED_YELLOW = 1;
			LED_GREEN = 1;
			delay_ms(T2);
			break;
			
		case YELLOWUP:
			LED_RED = 1;
			LED_YELLOW = 0;
			LED_GREEN = 1;
			delay_ms(T1);
			break;	
			
		case YELLOWDOWN:
			LED_RED = 0;
			LED_YELLOW = 0;
			LED_GREEN = 1;
			delay_ms(T1);
			break; 
			
		case GREEN:
			LED_RED = 1;
			LED_YELLOW = 1;
			LED_GREEN = 0;
			delay_ms(T2);
			break;  
			
		case YELLOWBLINK:
			LED_RED = 1;
			LED_YELLOW = 1;
			LED_GREEN = 1;
			delay_ms(T1);
			break;  
			
		case GREENWAVE:
			LED_RED = 1;
			LED_YELLOW = 1;
			LED_GREEN = 0;
			delay_ms(T3);	
			break;  
			
		default:
			LED_RED = 1;
			LED_YELLOW = 1;
			LED_GREEN = 1;
			break;
	}
}



				





				

