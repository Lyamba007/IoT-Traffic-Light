// The main library for creating the Wi-Fi connection
//
#include <ESP8266WiFi.h>

// A fully asynchronous TCP library, aimed at enabling trouble-free, 
// multi-connection network environment for Espressif's ESP8266 MCUs
//
#include <ESPAsyncTCP.h>

// The library for easy way building an asynchronous web server
//
#include <ESPAsyncWebServer.h>

// Include defines such as transitions, delays, inputs, outputs, leds
//
#include "defines.h"

static uint8_t state = YELLOWBLINK;    // Current state initialization
static uint8_t nextState; 			       // Variable for next state keeping

static bool  isActiveGreenWave= false; // "Green Wave" activation flag

// Set the timer variables for transition 
//
static unsigned long previousMillis = 0;
static unsigned short timerDelay = T1;

// Create AsyncWebServer object on port 80
//
static AsyncWebServer server(80);

// Replace with your network credentials
//
static char *ssid = "YOUR_WIFI";
static char * password = "YOUR_PASSWORD";

extern const char index_html[] PROGMEM; // HTML page code (server page)

// Main handle for returning the activated/deactivated Green Wave
//
static String processor(const String& var)
{  
  if (var == "greenwave")
  {
    return "Activated";
  }
  return String();
}


void setup() 
{
  // PINs for LED configuration 
  //
  pinMode(RED_LED,OUTPUT); 
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

  // PINs for tumblers
  //
  pinMode(ON_OFF, INPUT); 
  pinMode(TRANSITION, INPUT);

  // Initiate the WiFi connection
  //
  WiFi.begin(ssid, password);

  // Main request for initiating the communication with web server
  //
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Requests for getting the Green Wave
  //
  server.on("/greenwave", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // Requests for getting the activated Green Wave
    //
    if (request->hasParam("value")) 
    {
      AsyncWebParameter* valueParam = request->getParam("value");
      int value = valueParam->value().toInt();

      // Update your variable here
      //
      isActiveGreenWave = value;
  
      request->send_P(200, "text/plain", "Green Wave Activated");
    } 

    request->send_P(400, "text/plain", "Missing parameter");
  });

  // Start server
  //
  server.begin();
}


void loop() // Program entry point
{ 
  if (timerDelay <= millis() - previousMillis) 
  {
    previousMillis = millis();
    StateTransition(); 				// Automaton template function call
    state = nextState;				// Next state transition 
  }
}


void StateTransition() // Automaton template description
{ 
	// Transition function
	//
  switch(state)
  {
    case YELLOWBLINK:
			if(digitalRead(ON_OFF) == HIGH) // Get the Default state tumbler value 
				nextState = YELLOWUP;                   
			else 
        nextState = YELLOWBLINK;    
    break;
                      
    case YELLOWUP:
      if(digitalRead(ON_OFF) == LOW || digitalRead(TRANSITION) == LOW) //Get the transition tumbler state 
				nextState = YELLOWBLINK;
      else if (digitalRead(TRANSITION) == HIGH)
				nextState = REDLIGHT;   		 
    break;
              
    case REDLIGHT:
			if(digitalRead(ON_OFF) == LOW || digitalRead(TRANSITION) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(TRANSITION) == HIGH)
				nextState = YELLOWDOWN;
	  break;
          
    case YELLOWDOWN:
			if(digitalRead(ON_OFF) == LOW || digitalRead(TRANSITION) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(TRANSITION) == HIGH)
				nextState = GREENLIGHT;
			
			if(isActiveGreenWave)    // If the request was successfully processed
				nextState = GREENWAVE; // "Green Wave" transition        
    break; 
          
    case GREENLIGHT: 
			if(digitalRead(ON_OFF) == LOW || digitalRead(TRANSITION) == LOW)
				nextState = YELLOWBLINK;
			else if (digitalRead(TRANSITION) == HIGH)
				nextState = YELLOWUP;
    break;
    
    case GREENWAVE: // "Green Wave" state
			nextState = YELLOWUP;
      isActiveGreenWave = false; // Resetting the flag to turn on the mode  
    break;
		
		default:
      nextState = YELLOWBLINK;
    break;
  }
     
	// Outputs and delays function
	//	
  switch(state)
  { 
		case REDLIGHT: 
		  digitalWrite(RED_LED,HIGH);
			digitalWrite(YELLOW_LED,LOW);
			digitalWrite(GREEN_LED,LOW);
			timerDelay = T2; // Set the delay (timeout) by realized function call
    break;
      
    case YELLOWUP:
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      timerDelay = T1; 
    break;  
      
    case YELLOWDOWN:
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      timerDelay = T1; 
    break; 
      
    case GREENLIGHT:
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      timerDelay = T2; 
    break;  
      
    case YELLOWBLINK:
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
      timerDelay = T1; 
    break;  
      
    case GREENWAVE:
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      timerDelay = T3; 
		break;
  }
}  
