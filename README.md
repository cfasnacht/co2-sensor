# Simple CO2 Sensor PoC with display
Measures temperatur, CO2 level and humidity

<img src="https://github.com/cfasnacht/co2-sensor/blob/master/images/esp32-co2-sens.jpg" height="400">

## Hardware detail:

1. ESP32 with display and battery managment system
https://mikroshop.ch/?gruppe=3&artikel=1820
2. CO2 Sensor: Seeed Gove SCD30
http://wiki.seeedstudio.com/Grove-CO2_Temperature_Humidity_Sensor-SCD30/

## Wiring and setup:

| CO2 Sensor | Color      | ESP32 Pin  |
| ---------- | ---------- | ---------- |
| GND        | Black      | GND        |
| Vcc        | Red        | Vcc        |
| SDA        | White      | Pin 5      |
| SDL        | Yellow     | Pin 4      |

More details:

1. Display example usage, Wifi scaner:
https://github.com/hackffm/ESP32_OLED_WifiScanner/blob/master/ESP32_OLED_WifiScanner.ino

2. Wiring
http://www.areresearch.net/2018/01/how-to-use-ttgo-esp32-module-with-oled.html

3. CO2 sensor:
http://wiki.seeedstudio.com/Grove-CO2_Temperature_Humidity_Sensor-SCD30/

## Code:
[Simple Arduino IDE program to display the values from the sensors:](./ESP32_CO2_display.ino)

## Upload with Arduino IDE

1. Select Board:  Tools => Board => ESP32 Ardunio => WEMOS LOLIN32

2. Select Baud rate: Tools => Upload Speed => 115200

3. Select typical Port: Tools => /dev/ttyUSB0

4. Select Upload

5. Press Boot button on the board to enable flashing

## Old arduino version
[Arduino version](./arduino_version/README.md)
