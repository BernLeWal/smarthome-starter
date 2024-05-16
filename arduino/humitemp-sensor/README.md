# Humitemp-Sensor
Air-Sensor for the SHS (SmartHome-Starter) System.
It measures temperature and humidity.

## Bill-Of-Material (BOM)
- ESP32 Microcontroller-Board: WROOM-32 ESP32-S [Product Page](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf), [AliExpress](https://de.aliexpress.com/item/1005006476900011.html?spm=a2g0o.productlist.main.7.37d42g2j2g2j4H&algo_pvid=c82fd8fc-03ff-47af-97af-6229039ecbf2&aem_p4p_detail=2024051600205212092719442965540001734083&algo_exp_id=c82fd8fc-03ff-47af-97af-6229039ecbf2-3&pdp_npi=4%40dis%21EUR%2160.85%2115.45%21%21%21466.63%21118.44%21%402103010e17158440525233668e7440%2112000037341814397%21sea%21AT%210%21AB&curPageLogUid=Qfckn4DrLnUp&utparam-url=scene%3Asearch%7Cquery_from%3A&search_p4p_id=2024051600205212092719442965540001734083_1)
- DHT22 Sensor
- USB-C Cable

## Pre-Requisites

- Installed Arduino IDE (>2.0): see https://www.arduino.cc/en/software
- Install the ESP32-Board in Arduino IDE: see https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/
- Install the "DHT sensor library by Adafruit" in Arduino IDE: see https://randomnerdtutorials.com/esp32-mqtt-publish-dht11-dht22-arduino/


## References

- [ESP32 MQTT – Publish DHT11/DHT22 Temperature and Humidity Readings](https://randomnerdtutorials.com/esp32-mqtt-publish-dht11-dht22-arduino/)
- [DTH-sensor-library](https://github.com/adafruit/DHT-sensor-library)
