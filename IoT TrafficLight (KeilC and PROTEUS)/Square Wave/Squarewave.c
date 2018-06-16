
#include<reg52.h>
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P35 = P3^5;

sbit OUT=P1^2;    

void Init_Timer0(void)
{
 TMOD |= 0x01;	  
 EA=1;           
 ET0=1;          
 TR0=1;          
}

main()
{
	P1=0x00;
	P20=0; 
	P21=0; 
	P35=0;
	P1=0xFF;
 
 Init_Timer0();
 while(1);
}


void Timer0_isr(void) interrupt 1 using 1
{
 TH0=(65536-500)/256;		
 TL0=(65536-500)*256;      //1ms Square Wave  
                              

 OUT=~OUT;       
}