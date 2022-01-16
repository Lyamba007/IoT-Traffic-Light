//Libraries 
//
#include <ESP8266WiFi.h> 
#include <DNSServer.h>  
#include <ESP8266WebServer.h> 

//States initialization
//
#define YELLOWBLINK 1 //Default traffic light state
#define YELLOWUP 	2 //State after green light 
#define REDLIGHT  	3 
#define YELLOWDOWN 	4 //State after red light
#define GREENLIGHT  5
#define GREENWAVE 	6 //State with smartphone signal via WiFi

//Delays defines
//
#define T1 1000  //YELLOWBLINK, YELLOWUP, YELLOWDOWN states delay
#define T2 5000  //REDLIGHT, GREENLIGHT states delay
#define T3 15000 //GREENWAVE state delay

uint8_t state = YELLOWBLINK;  //Current state initialization
uint8_t nextState; 			  //Variable for next state keeping

bool activeGreenWave = false; //"Green Wave" activation flag

const char *ssid = "Traffic Light"; //The acces point (AP) name 

const byte DNS_PORT = 53;           //Select the DNS port value

IPAddress apIP(192, 168, 1, 1);		//Set the static IP address	
DNSServer dnsServer; 				//Create the DNS instance
ESP8266WebServer webServer(80);	  	//Set the port 80 for the web server


void handleRoot() //Request handler
{
  if(webServer.hasArg("t") == false) //If request has not got any parameters
	return;  //End of request handling
  
  activeGreenWave = true;  //If request has been handled correctly the "Green Wave" activates
}


void setup() 
{
  //PINs for LED configuration 
  //
  pinMode(12,OUTPUT); //RED LED  
  pinMode(14,OUTPUT); //YELLOW LED
  pinMode(16,OUTPUT); //GREEN LED

  WiFi.mode(WIFI_AP); //Select the mode of AP
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); //Set the IP and subnet mask
  WiFi.softAP(ssid);  //Create the AP by name

  webServer.on("/", handleRoot); //Initiate the server request-responce with created handler
  webServer.begin(); //Start the server
}


void loop() //Program entry point
{
	//It should be call each state after according to delay
	//
    dnsServer.processNextRequest(); //Ability to process a request when it is received
    webServer.handleClient(); 		//Request processing
    StateTransition(); 				//Automaton template function call
    state = nextState;				//Next state appropriation
}


void StateTransition()  //Automaton template description
{ 
	//Transition function
	//
    switch(state)
    {
		case YELLOWBLINK:
			if(digitalRead(4) == HIGH) //Get the Default state button value 
				nextState = YELLOWUP;                   
			else nextState = YELLOWBLINK;    
        break;
                      
        case YELLOWUP:
            if(digitalRead(4) == LOW || digitalRead(5) == LOW) //Get the transition button state 
				nextState = YELLOWBLINK;
            else if (digitalRead(5) == HIGH)
				nextState = REDLIGHT;   		 
        break;
              
        case REDLIGHT:
			if(digitalRead(4) == LOW || digitalRead(5) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(5) == HIGH)
				nextState = YELLOWDOWN;
		break;
          
        case YELLOWDOWN:
			if(digitalRead(4) == LOW || digitalRead(5) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(5) == HIGH)
				nextState = GREENLIGHT;
			
			if(activeGreenWave) //If the request was successfully processed
            {
				nextState = GREENWAVE;  //"Green Wave" transition
            }      
        break;
          
        case GREENLIGHT: 
			if(digitalRead(4) == LOW || digitalRead(5) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(5) == HIGH)
				nextState = YELLOWUP;
        break;
    
        case GREENWAVE: 							 //"Green Wave" regime
			nextState = YELLOWUP;
            activeGreenWave = false; 				 //Resetting the flag to turn on the mode
            webServer.send(200, "text/plain", "OK"); //Sending a positive result of the query to the client     
        break;
		
		default:
            nextState = YELLOWBLINK;
        break;
    }
     
	//Outputs and delays function
	//	
    switch(state)
    { 
		case REDLIGHT: 
			digitalWrite(12,HIGH);
			digitalWrite(14,LOW);
			digitalWrite(16,LOW);
			delay(T2); //Set the delay (timeout) by realized function call
         break;
      
        case YELLOWUP:
          digitalWrite(12,LOW);
          digitalWrite(14,HIGH);
          digitalWrite(16,LOW);
          delay(T1); 
        break;  
      
        case YELLOWDOWN:
          digitalWrite(12,LOW);
          digitalWrite(14,HIGH);
          digitalWrite(16,LOW);
          delay(T1); 
        break; 
      
        case GREENLIGHT:
          digitalWrite(12,LOW);
          digitalWrite(14,LOW);
          digitalWrite(16,HIGH);
          delay(T2);
        break;  
      
        case YELLOWBLINK:
          digitalWrite(12,LOW);
          digitalWrite(14,LOW);
          digitalWrite(16,LOW);
          delay(T1);
        break;  
      
        case GREENWAVE:
          digitalWrite(12,LOW);
          digitalWrite(14,LOW);
          digitalWrite(16,HIGH);
          delay(T3)
		break;
    }
}      
        
