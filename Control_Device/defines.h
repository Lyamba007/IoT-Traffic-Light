#ifndef __DEFINES_H__
#define __DEFINES_H__

//Pinout for DEMO LED
//
#define RED_LED    D6
#define YELLOW_LED D7
#define GREEN_LED  D8

//Main tumblers
//
#define ON_OFF     D3 
#define TRANSITION D5

//States initialization
//
#define YELLOWBLINK 1 //Default traffic light state
#define YELLOWUP 	  2 //State after green light 
#define REDLIGHT  	3 
#define YELLOWDOWN 	4 //State after red light
#define GREENLIGHT  5
#define GREENWAVE 	6 //State with smartphone signal via WiFi

//Delays defines
//
#define T1 1000  //YELLOWBLINK, YELLOWUP, YELLOWDOWN states delay
#define T2 5000  //REDLIGHT, GREENLIGHT states delay
#define T3 15000 //GREENWAVE state delay

#endif //__DEFINES_H__