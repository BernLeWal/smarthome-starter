# SmartHome-Starter (SHS)

A project to build a Smart-Home solution out of own IoT-Devices and software services.
Have fun!
<div align="right">Bernhard Wallisch, Mai 2024</div>

## Overview

```
SHS
└───arduino                         // Hardware devices with firmware
    ├───humitemp-sensor             // HumiTemp-Sensor to measure temperature and humidity
    └───test-esp32_blinking_led     // Testapplication to verify correct IDE-setup with ESP32
```

## Getting started

1. Buy your first ESP32 and get to know your Arduino developing environment in [arduino/test-esp32_blinking_led/](./arduino/test-esp32_blinking_led/README.md)

2. Build your first Sensor - a HumiTemp sensor to measure temperature and humidity - using the guide in [arduino/humitemp-sensor/](./arduino/humitemp-sensor/README.md). THis guide shows also how to configure your MQTT-Client or MQTT-Dashboard Android App to watch your readings.

## Entry Points

### MQTT:

- Online MQTT-Client: https://testclient-cloud.mqtt.cool/  
  This will only work for MQTT-Brokers which are available over the internet, like test.mosquitto.org.
- Offline MQTT-Client (to be installed on your computer): https://mqttx.app/
  This will also work for the local MQTT-Broker in this project

