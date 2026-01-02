# Iot-smart-dashboard
A WiFi-enabled smart desk display using ESP32 and a 16×2 parallel LCD. It shows real-time 12-hour clock via NTP, live weather data (temperature &amp; humidity) from OpenWeatherMap updated every 30 minutes, and a Pomodoro timer that runs continuously without resetting when modes are switched using a push button.
<img width="1532" height="782" alt="image" src="https://github.com/user-attachments/assets/d7b6774e-1979-491f-be6c-f8727d8ad9db" />
<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/1f4be8bc-d3bf-438c-bb76-bee0382bac77" />
<img width="900" height="1600" alt="image" src="https://github.com/user-attachments/assets/fa4c81bc-baf0-48ff-9229-399ec5c2f2c0" />

---

**Time • Weather • Pomodoro Timer**

## 📌 Overview

This project is a WiFi-enabled smart desk display built using an **ESP32** and a **16×2 parallel LCD**. It displays real-time clock (12-hour format), live weather data, and a Pomodoro focus timer. A single push button is used to switch between modes. The system uses non-blocking timing, so all features run smoothly without resets.

---

## ✨ Features

* ⏰ Real-time clock via NTP (12-hour format)
* 🌦 Live temperature & humidity from OpenWeatherMap
* 🔄 Weather auto-updates every 30 minutes
* 🍅 Pomodoro timer (runs in background, no reset on mode switch)
* 🔘 Mode switching using one push button
* ❌ No I2C module (parallel LCD control)

---

## 🧰 Components Used

* ESP32 Development Board
* 16×2 LCD (HD44780 compatible)
* 10kΩ potentiometer (LCD contrast)
* Push button
* 3.3k–10kΩ resistor (button pull-up if needed)
* Breadboard
* Jumper wires
* USB cable

---

## 🔌 Wiring Connections

### LCD → ESP32

| LCD Pin | Function        | ESP32 GPIO     |
| ------- | --------------- | -------------- |
| RS      | Register Select | 23             |
| EN      | Enable          | 22             |
| D4      | Data            | 21             |
| D5      | Data            | 19             |
| D6      | Data            | 18             |
| D7      | Data            | 5              |
| VSS     | GND             | GND            |
| VDD     | VCC             | 5V             |
| V0      | Contrast        | Pot middle pin |
| A       | Backlight +     | 5V             |
| K       | Backlight −     | GND            |

### Button

* One side → GPIO 15
* Other side → GND
* Uses `INPUT_PULLUP`

---

## 🌐 Software Requirements

* Arduino IDE
* ESP32 Board Package
* Libraries:

  * `WiFi.h`
  * `HTTPClient.h`
  * `ArduinoJson`
  * `LiquidCrystal`
  * `time.h`

---

## ⚙ How It Works

* ESP32 connects to WiFi
* Time is synced via NTP server
* Weather data fetched using HTTP + JSON parsing
* `millis()` is used for non-blocking timing
* Button cycles through Time → Weather → Pomodoro

---

## 🚀 Future Improvements

* Weather icons using custom LCD characters
* Touch or capacitive button input
* Buzzer alert for Pomodoro completion
* OLED or TFT upgrade

---

