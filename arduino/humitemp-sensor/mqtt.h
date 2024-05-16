#ifndef MQTT_H
#define MQTT_H

#include "wifi.h"

//Libraries for MQTT connection
#include <ArduinoMqttClient.h>

// Setup MQTT
MqttClient mqttClient(espClient);


void connectToMQTT() {
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
 
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
 
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

#endif // MQTT_H