#include <Arduino.h>

// Variable for Motion Detected
int motionDetected = 0;
 
// Variable to store value from PIR
int pirValue; 


int laserPin = 11;
int pirPin = 7;

void setup() {
  pinMode(laserPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  // delay(60000);
}

void loop() {
  
  // Get value from motion sensor
	pirValue = digitalRead(pirPin);
	// See if motion Detected
	if (pirValue == 1){
		// turn laser on for 3 seconds
		digitalWrite(laserPin, HIGH);
		Serial.print("Motion Detected!");
		delay(5000);
    digitalWrite(laserPin, LOW); // Turn off the laser head
    delay(5000); 
  }
    

}
