# ESP32 IoT Temperature & Humidity Monitor

This project demonstrates how to interface an **ESP32** with a **DHT22** sensor to monitor real-time temperature and humidity data. The project is fully integrated with **Blynk IoT Cloud**, allowing remote data visualization and LED control.

## Features
- **DHT22 Integration:** Accurate temperature and humidity sensing.
- **Blynk Cloud Dashboard:** Real-time data visualization via mobile/web.
- **Remote Actuation:** Control an onboard/external LED from anywhere.
- **Wokwi Ready:** Fully simulated environment for testing without hardware.

## Components
- ESP32 Development Board
- DHT22 Sensor
- LED (Generic)
- Resistors/Wiring as per Wokwi diagram

## Setup Instructions
1. **Blynk Setup:** Create a new Template on Blynk.
2. **Credentials:** Copy your `BLYNK_TEMPLATE_ID`, `BLYNK_TEMPLATE_NAME`, and `BLYNK_AUTH_TOKEN`.
3. **Configure Code:** Paste these credentials into the `sketch.ino` file provided in this repository.
4. **Run:** Upload to ESP32 or start the Wokwi simulation.
