// c51_delay.h

#ifndef _C51_DELAY__H_
#define _C51_DELAY__H_

#include <reg52.h> 

/**
 * 	C51 Delays Library by Shurick
 *	Provide delay methods based on C51 Timer1
 *	NOTE: Calculations are made for standard 12 MHz clock
 * 	Make sure that Timer1 in C51 is NOT used by another procedure,
 *	because previous timer1 state will be broken.
 * 	Provided Interface:
 *		void delay_us(unsigned int dval) : Delay in microseconds
 * 		void delay_ms(unsigned int dval) : Delay in milliseconds
 */

// Wait specified amount of time, in microseconds
void delay_us(unsigned int dval);

// Wait specified amount of time, in milliseconds
void delay_ms(unsigned int dval);

/*
//=============== TIMER 0 =================
// Timer0 Init
void Init_Timer0(void)
{
// TMOD (89h) SFR
// Bit	Name	Timer	Explanation of Function	
// 7	GATE1	1		When this bit is set the timer will only run when INT1 (P3.3) is high. When this bit is clear the timer will run regardless of the state of INT1.
// 6	C/T1	1		When this bit is set the timer will count events on T1 (P3.5). When this bit is clear the timer will be incremented every machine cycle.
// 5	T1M1	1		Timer mode bit (see below)
// 4	T1M0	1		Timer mode bit (see below)
// 3	GATE0	0		When this bit is set the timer will only run when INT0 (P3.2) is high. When this bit is clear the timer will run regardless of the state of INT0.
// 2	C/T0	0		When this bit is set the timer will count events on T0 (P3.4). When this bit is clear the timer will be incremented every machine cycle.
// 1	T0M1	0		Timer mode bit (see below)
// 0	T0M0	0		Timer mode bit (see below)
//------------------------------------------------
// TxM1	TxM0	Timer Mode	Description of Mode
// 0	0		0			13-bit Timer.
// 0	1		1			16-bit Timer
// 1	0		2			8-bit auto-reload
// 1	1		3			Split timer mode
//------------------------------------------------
	TMOD |= 0x01;		// use 16bit timer	(0x02 for 8bit count)
	EA=1;          		// interrupt enable
	ET0=1;           	// timer 0 overflow interrupt enable
	TR0=1;          	// start timer
}
*/

#endif // _C51_DELAY__H_