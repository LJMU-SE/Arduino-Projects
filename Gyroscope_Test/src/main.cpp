#include <Wire.h>                      // This includes the Wire library for I2C communication
#include <Adafruit_MPU6050.h>          // This includes the MPU6050 library for interfacing with the sensor
#include <Adafruit_Sensor.h>           // This includes the Adafruit Sensor library for handling sensor events

Adafruit_MPU6050 mpu;   

bool isLevel(float roll, float pitch) {
  // You can adjust the threshold values based on your definition of "level"
  return (abs(roll) < 2.0 && abs(pitch) < 2.0);  // Return true if both roll and pitch are within a small threshold, indicating a level orientation
}                // Create an instance of the MPU6050 sensor

void setup() {
    Serial.begin(9600);                   // Initialize serial communication at 9600 baud rate
    if (!mpu.begin()) {                   // Check if the MPU6050 sensor is connected and initialized
        Serial.println("Failed to find MPU6050!");  // Print an error message if the sensor is not found
        while (1);                         // Loop indefinitely if the sensor initialization fails
    }
    Serial.println("Connestion established with MPU6050");
}

void loop() {
    sensors_event_t a, g, temp;           // Create variables to store sensor events (acceleration, gyroscope, temperature)
    mpu.getEvent(&a, &g, &temp);          // Read sensor events from the MPU6050 sensor

    float roll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;  // Calculate the roll angle using accelerometer data
    float pitch = atan(-a.acceleration.x / sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;  // Calculate the pitch angle

    Serial.print("Roll: ");
    Serial.print(roll);                   // Print the roll angle to the serial monitor
    Serial.print(" Pitch: ");
    Serial.print(pitch);                  // Print the pitch angle to the serial monitor

    if (isLevel(roll, pitch)) {           // Check if the orientation is level using the custom function isLevel
        Serial.println(" - Level");        // If level, print "Level" to the serial monitor
    } else {
        Serial.println(" - Not Level");    // If not level, print "Not Level" to the serial monitor
    }

    delay(500);                           // Add a delay to make the output readable, adjust as needed
}