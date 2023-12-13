#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

const char* SSID = "espWifi";
const char* PASSWORD = "ljmu1111";

const int BUTTON_PIN = 2;
const char* jokesAPI = "https://v2.jokeapi.dev/joke/Programming?type=twopart";

// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

enum State{
  CONNECTING,
  GETTING_JOKE,
  IDLE
};

State current;

void getJoke();
void connectToWifi();

void setup(){

  // Initialise Serial and button pin
  Serial.begin(115200);
  pinMode(BUTTON_PIN,INPUT);

  // Set initial state
  current = CONNECTING;

}

void loop() {

  // State action switch case
  switch(current){

    case CONNECTING:
      connectToWifi();
      break;

    case GETTING_JOKE:
      getJoke();
      break;

    case IDLE:
      break;

  }

  // State change switch

  if (digitalRead(BUTTON_PIN) == HIGH){

      switch(current){

        case CONNECTING:
          break;

        case GETTING_JOKE:
          break;

        case IDLE:
          Serial.println("Button pressed, getting joke....");
          current = GETTING_JOKE;
          break;
      
  }

  
  }

  
  
}

void connectToWifi(){

    // Initialise wifi connection 
    WiFi.begin(SSID, PASSWORD);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to WiFi");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    // After successful connection change state to idle
    current = IDLE;
}


void getJoke(){

  // Initialise http instance on api url
  HTTPClient http;
  http.begin(jokesAPI);

  // http instance will return -1 if request error
  int httpResponseCode = http.GET();

  if (httpResponseCode < 0) {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":(");
    Serial.print("HTTP Response:");
    Serial.println(httpResponseCode);
    return;
  }

  // Get serialised json response from API then deserialise
  String response = http.getString();
  
  DynamicJsonDocument responseAsJson(1024); 
  deserializeJson(responseAsJson, response);

  String setup = responseAsJson["setup"];
  String punchline = responseAsJson["delivery"];

  Serial.println(setup);
  Serial.println(punchline);

  http.end();

  // Change state back to idle on function exit 
  current = IDLE;
}