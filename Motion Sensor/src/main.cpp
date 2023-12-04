#include <Arduino.h>

 
// Variable to store value from PIR 
int pirValue; 
bool motionDetected;

unsigned long lastChangeTime;
const int DELAY = 2000;

int laserPin = 11;
int pirPin = 7;

enum State{
  LASER_ON,
  LASER_OFF
};

State current;

// Stolen from DJ Lamb TY#
// Giving warning for comparison between signed and unsigned int....
boolean timeDiff(unsigned long start, int specifiedDelay) {
  return (millis() - start >= specifiedDelay);
}

void setup() {

  // Set current state and change time
  current = LASER_OFF;
  lastChangeTime=0;

  // Setup pins
  pinMode(laserPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);

  // Wait for one minute to properly initialise sensor
  Serial.println("Preparing sensor.....");
  delay(60000);
  Serial.println("Ready to go!");
}



void loop() {
  
  State old = current;

  // Get value from motion sensor
  if (digitalRead(pirPin) == HIGH){
    motionDetected = true;
  }
  else {
    motionDetected = false;
  }

	// See if motion detected 
	if (motionDetected && timeDiff(lastChangeTime,DELAY)) {

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

  // If state change made this iteration, update the lastChangeTime variable
  if (old != current){
    lastChangeTime = millis();
  }
    
}
