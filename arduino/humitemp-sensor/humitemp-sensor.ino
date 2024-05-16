/*
Air-Sensor for the SHS (SmartHome-Starter) System
It measures temperature and humidity
*/

#include <Arduino.h>
#include "config.h" // configuration settings (WIFI SSID, MQTT Broker,...)
#include "wifi.h"   // utilities to use WiFi
#include "mqtt.h"   // utilities to use MQTT

// Libraries for DHT22 sensor
#include "DHT.h"


// Setup for the ESP32
uint64_t chipid;
bool device_info_displayed = false;

void display_device_info() {
  Serial.println("SHS HumiTemp-Sensor");
  Serial.printf("Device ID=%llX\n", chipid);
}


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

int readingID = 0;    //packet counter

void sendDataMQTT(String subtopic, float value) {
  char datatopic[128];
  char output[128];

  snprintf(datatopic, 128, "%s/%llX/%s", topic, chipid, subtopic);
  snprintf(output, 128, "%2.1f", value);
  mqttClient.beginMessage(datatopic);
  mqttClient.print(output);
  mqttClient.endMessage();
  Serial.printf("MQTT data #%d sent to %s: data=%s \n", readingID++, datatopic, output);
}



 
void setup() {
  Serial.begin(115200);
  display_device_info();
  chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).

  dht.begin();
  pinMode(LEDPIN, OUTPUT);

  connectToWiFi();
  connectToMQTT();
  Serial.println("setup done");  
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   // Save the last time a new reading was published


    if (!device_info_displayed) {
      display_device_info();
      device_info_displayed = true;
    }

    digitalWrite(LEDPIN, HIGH); // Blink the LED

    hum = dht.readHumidity(); // New DHT sensor readings
    temp = dht.readTemperature();     // Read temperature as Celsius 
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(temp) || isnan(hum)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    Serial.printf("Measured Temp=%2.1f°C, Humi=%2.1f%%\n", temp, hum);

    sendDataMQTT("temp", temp);
    sendDataMQTT("hum", hum);

    digitalWrite(LEDPIN, LOW);
  }
}
