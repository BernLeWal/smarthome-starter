/*
Air-Sensor for the SHS (SmartHome-Starter) System
It measures temperature and humidity
*/

#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 4
#define LEDPIN 2

// Uncomment whatever DHT sensor type you're using
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)  

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold sensor readings
float temp;
float hum;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 10000;        // Interval at which to publish sensor readings


void setup() {
  Serial.begin(115200);
  Serial.println("SHS HumiTemp-Sensor");

  dht.begin();
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   // Save the last time a new reading was published

    digitalWrite(LEDPIN, HIGH); // Blink the LED

    hum = dht.readHumidity(); // New DHT sensor readings
    temp = dht.readTemperature();     // Read temperature as Celsius 
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(temp) || isnan(hum)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    Serial.printf("Temp=%2.1f°C, Humi=%2.1f%%\n", temp, hum);

    digitalWrite(LEDPIN, LOW);
  }
}
