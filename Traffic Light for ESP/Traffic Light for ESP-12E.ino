#include <ESP8266WiFi.h> 
#include <DNSServer.h>  
#include <ESP8266WebServer.h> 

#define YELLOWBLINK 1 // States and time parameteres declaring
#define YELLOWUP 2  
#define REDLIGHT  3
#define YELLOWDOWN 4
#define GREENLIGHT  5
#define GREENWAVE 6

#define T1 1000
#define T2 5000
#define T3 T2*3

int state = YELLOWBLINK; //Current state initialization
int nextState; //Variable for next state keeping

bool activeGreenWave = false; //"Green Wave" activated flag

const char *ssid = "Traffic Light"; 

const byte DNS_PORT = 53;  

IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer; 
ESP8266WebServer webServer(80);  


void handleRoot() //Request handler
{
  if(webServer.hasArg("t") == false) //If request has not got any parameters
  {
      return;  //End of request handling
  }
    
  activeGreenWave = true;  //If request has been handled correctly the "Green Wave" activates
}


void setup() 
{
  pinMode(12,OUTPUT); //LED connection  
  pinMode(14,OUTPUT); //
  pinMode(16,OUTPUT);

  WiFi.mode(WIFI_AP); 
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); 
  WiFi.softAP(ssid); 

  webServer.on("/", handleRoot); 
  webServer.begin(); 
}


void loop() //Program entry point
{
    dnsServer.processNextRequest(); //Ability to process a request when it is received
    webServer.handleClient(); //Request processing
    StateTransition(); //Inputs and outputs function call
    state = nextState; //Next state appropriation
}


void StateTransition()  //Inputs and outputs function description
{ 
       switch(state)
       {
         case YELLOWBLINK:
           
              if(digitalRead(4) == HIGH) //Button read
              {                                 
                  nextState = YELLOWUP;                 
              }
            
              else if(digitalRead(4) == LOW) 
              {
                  nextState = YELLOWBLINK;
              }
            
              break;
                      
          case YELLOWUP:
              
              if(digitalRead(4) == LOW || digitalRead(5) == LOW)
              {
                  nextState = YELLOWBLINK;
              }
              
              else if (digitalRead(5) == HIGH)
              {
                  nextState = REDLIGHT;   
              } 
              
              break;
              
          case REDLIGHT:
          
              if(digitalRead(4) == LOW || digitalRead(5) == LOW)
              {
                  nextState = YELLOWBLINK;
              }
              
              else if (digitalRead(5) == HIGH)
              {
                  nextState = YELLOWDOWN;
              } 
              
              break;
          
          case YELLOWDOWN:

              if(digitalRead(4) == LOW || digitalRead(5) == LOW)
              {
                  nextState = YELLOWBLINK;
              }
              
              else if (digitalRead(5) == HIGH)
              {
                  nextState = GREENLIGHT;
              }
               
              if(activeGreenWave) //If the request was successfully processed
              {
                nextState = GREENWAVE;  //Direct activation of the "Green Wave"
              }
              
              break;
          
          case GREENLIGHT: 

              if(digitalRead(4) == LOW || digitalRead(5) == LOW)
              {
                  nextState = YELLOWBLINK;
              }
              
              else if (digitalRead(5) == HIGH)
              {
                  nextState = YELLOWUP;
              } 
              
              break;
    
            
          case GREENWAVE: //"Green Wave" regime
  
                nextState = YELLOWUP;
                activeGreenWave = false; //Resetting the flag to turn on the mode
                webServer.send(200, "text/plain", "OK"); //Sending a positive result of the query to the client
              
              break;

            
          default:
              nextState = YELLOWBLINK;
              break;
      }
      
      switch(state)
      { 
        case REDLIGHT: 
          digitalWrite(12,HIGH);
          digitalWrite(14,LOW);
          digitalWrite(16,LOW);
          delay(T2); //System function of the state for a certain amount of time
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
          delay(T3); 
      }
}      
        
