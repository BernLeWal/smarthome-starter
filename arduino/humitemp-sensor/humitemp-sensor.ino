/*
Air-Sensor for the SHS (SmartHome-Starter) System
It measures temperature and humidity
*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h" // configuration settings (WIFI SSID, MQTT Broker,...)

#include "esp32.h"        // utilities for the ESP32
#include "esp32-wifi.h"   // utilities to use WiFi
#include "esp32-mqtt.h"   // utilities to use MQTT


// Libraries for DHT22 sensor
#include "DHT.h"


// Setup for the DHT22 sensor
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


char topic_hum[128];
char topic_temp[128];
char topic_json[128];

void sendDataJSON() {
  StaticJsonDocument<48> doc;
  char output[128];
  doc["id"] = WiFi.macAddress(); //String(deviceid, HEX);
  doc["type"] = "humitemp";
  doc["temp"] = temp;
  doc["hum"] = hum;
  doc["pressure"] = -1;

  serializeJson(doc, output);

  sendDataMQTT(topic_json, output);
}

 
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);

  get_device_info();
  display_device_info();

  dht.begin();

  connectToWiFi();
  connectToMQTT();

  snprintf(topic_temp, 128, "%s/%X/temp", topic, deviceid);
  snprintf(topic_hum, 128, "%s/%X/hum", topic, deviceid);
  snprintf(topic_json, 128, "%s/%X", topic, deviceid);

  Serial.println("Setup done");  
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

    Serial.printf("Measured Temp=%2.1f°C, Humi=%2.1f%%\n", temp, hum);

    sendDataMQTT(topic_temp, String(temp,1));
    sendDataMQTT(topic_hum, String(hum,1));
    sendDataJSON();

    digitalWrite(LEDPIN, LOW);
  }
}
