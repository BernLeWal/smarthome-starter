#ifndef ESP32_H
#define ESP32_H

// Setup for the ESP32
uint64_t chipid;
uint16_t deviceid;

void get_device_info() {
  chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  deviceid = (uint16_t)(chipid & 0xFFFF);
}

void display_device_info() {
  Serial.println("Device Type=SHS HumiTemp-Sensor");
  Serial.printf("Device ID=%X\n", deviceid);
  Serial.printf("Chip ID=%llX\n", chipid);
}

#endif // ESP32_H