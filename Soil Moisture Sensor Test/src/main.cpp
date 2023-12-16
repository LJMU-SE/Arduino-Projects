#include <arduino.h>
int airValue = 1000;   
int waterValue = 250;   

int soilMoistureValue = 0;
int soilMoisturePercent = 0;

enum State{
  LOW,
  MED,
  HIGH
}

void setup() {
      // Set the baud rate to 9600 bps
      Serial.begin(9600); 
      State soilLevel; 
}

void loop() {

      // Read value from sensor
      soilMoistureValue = analogRead(36);  
      Serial.println(soilMoistureValue);
      
      // Map the value between no moisture and submerged in water
      soilMoisturePercent = map(soilMoistureValue,airValue, waterValue, 0, 100);

      // Change states accordingly 
      if(soilMoisturePercent >= 80 )
      {
        soilLevel = HIGH;
      }
      else if(soilMoisturePercent < 80 && soilMoisturePercent >= 20){
        soilLevel = MED;
      }
      else if (soilMoisturePercent < 20){
        soilLevel = LOW;
      }
      delay(6000);
}
        
