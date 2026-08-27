🌦️ Wireless Weather Station with ESP32-C3 and E01

A low-power wireless weather station built using an ESP32-C3 SuperMini, AHT10 temperature and humidity sensor, EBYTE E01 2.4GHz radio module, and an ESP32-WROOM gateway equipped with an SSD1306 OLED display.

The system continuously measures ambient temperature and relative humidity, transmitting the measurements wirelessly to a central gateway that displays the data in real time.

📷 Project Overview

This project consists of two main devices:

Remote Sensor Node
ESP32-C3 SuperMini
AHT10 Temperature & Humidity Sensor
EBYTE E01 RF Module
LiPo Battery Powered
Gateway
ESP32-WROOM
EBYTE E01 RF Module
SSD1306 OLED Display (128x64)
>The sensor node collects environmental data and sends it via RF to the gateway.

🔧 Hardware
Sensor Node
ESP32-C3 SuperMini
AHT10 Temperature & Humidity Sensor
EBYTE E01 RF Module
3.7V LiPo Battery
AMS1117-3.3 Voltage Regulator
Decoupling Capacitors
Gateway
ESP32-WROOM
EBYTE E01 RF Module
SSD1306 OLED Display (128x64)

📡 Wireless Communication

Communication is handled using the RF24 library and EBYTE E01 radio modules operating at 2.4 GHz.

Settings
Channel: 100
Data Rate: 250 Kbps
Power Level: LOW

Data Packet Structure
struct WeatherData
{
    float temperature;
    float humidity;
    uint32_t counter;
};

🔌 Wiring
ESP32-C3 + AHT10
AHT10         ESP32-C3
VCC       -> 3.3V
GND       -> GND

SDA       -> GPIO0
SCL       -> GPIO1


ESP32-C3 + E01
E01           ESP32-C3

VCC       -> 3.3V
GND       -> GND

CE        -> GPIO20
CSN       -> GPIO21

SCK       -> GPIO4
MISO      -> GPIO5
MOSI      -> GPIO6

Gateway ESP32-WROOM + E01
E01           ESP32-WROOM

VCC       -> 3.3V
GND       -> GND

CE        -> GPIO22
CSN       -> GPIO21

SCK       -> GPIO18
MISO      -> GPIO19
MOSI      -> GPIO23


Gateway ESP32-WROOM + OLED
OLED          ESP32-WROOM

VCC       -> 3.3V
GND       -> GND

SDA       -> GPIO26
SCL       -> GPIO27

📺 Gateway Display

The OLED shows real-time environmental information received from the remote station:

REMOTE STATION

T:24.5°C

H:61.2%

If communication is lost:
NO
SIGNAL

🧪 Testing

The system successfully passed several validation tests:

✅ Temperature reading validation

✅ Humidity reading validation

✅ Radio communication testing

✅ OLED display testing

✅ Long-duration runtime testing

✅ Low-temperature testing

During development, the AHT10 sensor was tested inside a household freezer and successfully measured temperatures down to approximately:]
-5°C
confirming proper operation under low-temperature conditions.

🔋 Power Supply

The remote sensor node is powered by:
3.7V LiPo Battery

regulated through an:
AMS1117-3.3

providing stable power to:

ESP32-C3
AHT10
E01 RF Module

Additional filtering capacitors are used to improve RF stability and minimize voltage drops during radio transmissions.

🚀 Future Improvements
Deep Sleep operation
Battery voltage monitoring
Solar charging support
Weatherproof enclosure
BMP280/BME280 pressure sensor
Light intensity sensor
MQTT integration
Home Assistant integration
Historical data logging
Multiple remote sensor nodes

📈 Project Status

✅ Fully Operational

✅ Wireless Temperature Monitoring

✅ Wireless Humidity Monitoring

✅ OLED Gateway Display

✅ LiPo Battery Support

✅ RF Communication Verified


📄 License

This project was developed for educational purposes and as a practical IoT, embedded systems, and wireless communication experiment using ESP32 microcontrollers.

⭐ If you found this project useful, consider giving the repository a star!




















