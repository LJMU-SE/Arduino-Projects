#include <Arduino.h>

// Variable to store value from PIR 
int pirValue; 
bool motionDetected;

unsigned long lastChangeTime;
const int DELAY = 2000;
const int PIR_DELAY = 30000;

int laserPin = 11;
int pirPin = 7;

enum State{
  LASER_ON,
  LASER_OFF,
  WARM_UP
};

State current;

// Stolen from DJ Lamb TY#
// Giving warning for comparison between signed and unsigned int....
boolean timeDiff(unsigned long start, int specifiedDelay) {
  return (millis() - start >= specifiedDelay);
}

void setup() {

  // Set current state and change time
  current = WARM_UP;
  lastChangeTime=0;
  

  // Setup pins
  pinMode(laserPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  Serial.println("Preparing sensor.....");


}



void loop() {

  // Wait for one minute to properly initialise sensor
  if (millis() >= PIR_DELAY && current == WARM_UP){
      Serial.println("Ready to go!");
      current = LASER_OFF;
  }
  
  // This seems smelly idk....
  if (current != WARM_UP){
    
      State old = current;
      // Get value from motion sensor 
      motionDetected = (digitalRead(pirPin) == HIGH);

      // See if motion detected 
      if (motionDetected) {

        // If delay time has passed letting PIR sensor reset 
        if(timeDiff(lastChangeTime,DELAY)){

            switch(current){

            case LASER_OFF:
              Serial.println("Turning light on!");
              digitalWrite(laserPin, HIGH);
              current = LASER_ON;
              
              break;

            case LASER_ON:
              Serial.println("Turning light off!");
              digitalWrite(laserPin, LOW); 
              current = LASER_OFF;
              
              break;

          } 

        }
        
      }

      // If state change made this iteration, update the lastChangeTime variable
      if (old != current){
        lastChangeTime = millis();
      }

  }
  
    
}
