#ifndef ESP32_WIFI_H
#define ESP32_WIFI_H

//Libraries for Web connection
#include <WiFi.h>

#define BUILTIN_LED 2

void printStatus() {
  switch ( WiFi.status() ) {
    case WL_IDLE_STATUS : Serial.print("IDLE "); break;
    case WL_NO_SSID_AVAIL : Serial.print("NO_SSID "); break;
    case WL_SCAN_COMPLETED : Serial.print("SCAN "); break;
    case WL_CONNECTED : Serial.print("CONN "); break;
    case WL_CONNECT_FAILED : Serial.print("FAIL "); break;
    case WL_CONNECTION_LOST : Serial.print("LOST "); break;
    case WL_DISCONNECTED : Serial.print("DISC "); break;
    default: Serial.print("unknown");
  }
  //Serial.printf("%d ", WiFi.status() );
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);
  Serial.print("Connecting to "); Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED) // waitForConnectResult
  {
    // Serial.prinf('.');
    printStatus();
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


#endif // ESP32_WIFI_H