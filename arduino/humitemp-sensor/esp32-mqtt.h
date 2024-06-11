#ifndef ESP32_MQTT_H
#define ESP32_MQTT_H

#include "esp32-wifi.h"

//Libraries for MQTT connection
#include <ArduinoMqttClient.h>
#include <WiFiClientSecure.h>

// Setup MQTT
WiFiClientSecure espClient;
MqttClient mqttClient(espClient);



void connectToMQTT() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.print(mqtt_broker);
  Serial.print(" on port ");
  Serial.println(mqtt_port);
 
  if (strlen(caCert) > 0) {
    espClient.setCACert(caCert);
  }
  mqttClient.setId("HumiTemp-Sensor");
  if ( strlen(mqtt_user) > 0 ) {
    mqttClient.setUsernamePassword(mqtt_user, mqtt_pwd);
  } 
  if (!mqttClient.connect(mqtt_broker, mqtt_port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    Serial.println("   Restart");
    delay(5000);
    ESP.restart();
  }
 
  Serial.println("Connected to the MQTT broker!");
  Serial.println();
}


int readingID = 0;    //packet counter

void sendDataMQTT(String topic, String data) {
  if (!mqttClient.connected()) {
    connectToMQTT();
  }

  mqttClient.beginMessage(topic);
  mqttClient.print(data);
  mqttClient.endMessage();
  Serial.printf("MQTT data #%d sent to %s: data=%s \n", readingID++, topic.c_str(), data.c_str());
}
#endif // ESP32_MQTT_H