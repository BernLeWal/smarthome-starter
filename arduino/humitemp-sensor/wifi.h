#ifndef WIFI_H
#define WIFI_H

//Libraries for Web connection
#include <WiFi.h>

#define BUILTIN_LED 2

WiFiClient espClient;

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
 
    if ((++i % 16) == 0)
    {
      //Serial.println(F(" still trying to connect"));
      Serial.println(F("Restart"));
      delay(500);
      ESP.restart();
    }
  }
 
  Serial.print(F("Connected. My IP address is: "));
  Serial.println(WiFi.localIP());
 
  if(WiFi.status() == WL_CONNECTED) {
    for (i=0;i<4;i++) {
      digitalWrite(BUILTIN_LED,LOW);
      delay(100);
      digitalWrite(BUILTIN_LED,HIGH);
      delay(100);
      Serial.print(F("blink "));
      digitalWrite(BUILTIN_LED, LOW);
      }
  }
}


#endif // WIFI_H