# Test-esp32_blinking_led

Simple application to verify the correct setup of Arduino IDE with ESP32 board.
In this demo the following board was used: WROOM-32 ESP32-S.

## Bill-Of-Material (BOM)
- ESP32 Microcontroller-Board: WROOM-32 ESP32-S [Product Page](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf), [AliExpress](https://de.aliexpress.com/item/1005006476900011.html?spm=a2g0o.productlist.main.7.37d42g2j2g2j4H&algo_pvid=c82fd8fc-03ff-47af-97af-6229039ecbf2&aem_p4p_detail=2024051600205212092719442965540001734083&algo_exp_id=c82fd8fc-03ff-47af-97af-6229039ecbf2-3&pdp_npi=4%40dis%21EUR%2160.85%2115.45%21%21%21466.63%21118.44%21%402103010e17158440525233668e7440%2112000037341814397%21sea%21AT%210%21AB&curPageLogUid=Qfckn4DrLnUp&utparam-url=scene%3Asearch%7Cquery_from%3A&search_p4p_id=2024051600205212092719442965540001734083_1)
- USB-C Cable

## Pre-Requisites

- Installed Arduino IDE (>2.0): see https://www.arduino.cc/en/software
- Install the ESP32-Board in Arduino IDE: see https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/

## Setup

* Start the Arduino IDE
* Toolbar: Select Board / Select Other Board and Port  
  A Dialog Box opens showing a List of Ports on the right hand side
    * Connect your ESP32 Board via USB to your computer  
      The COM?-Port for your device will appear --> Select it
    * Search for your Board: here it was "WROOM"
    * Select "ESP32-WROOM-DA Module"

## Running

* Open the [test-esp32_blinking_led.ino](test-esp32_blinking_led.ino) - File
* Click on the ```[->]``` button


## References

- [Getting Started with VS Code and PlatformIO IDE for ESP32 and ESP8266 (Windows, Mac OS X, Linux Ubuntu)](https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/)