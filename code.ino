#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include "time.h"

LiquidCrystal lcd(23, 22, 21, 19, 18, 5);

#define BTN 15

const char* ssid = "your ssid";
const char* password = "ur pass here";

String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "ur api";

String lat = "copy from your location in google maps";
String lon = " ' ' ' ' '";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 21600;
const int daylightOffset_sec = 0;

int mode = 0;
bool lastState = HIGH;

float temp = 0;
int hum = 0;

unsigned long lastWeatherUpdate = 0;
const unsigned long weatherInterval = 30UL * 60UL * 1000UL;

String lastUpdated = "";

int pomodoroMin = 25;
int pomodoroSec = 0;
bool pomodoroRun = true;
unsigned long prevMillis = 0;

String getTime12() {
  struct tm t;
  if (!getLocalTime(&t)) return "NA";
  int h = t.tm_hour;
  String ap = "AM";
  if (h >= 12) {
    ap = "PM";
    if (h > 12) h -= 12;
  }
  if (h == 0) h = 12;
  char buf[20];
  sprintf(buf, "%02d:%02d:%02d %s", h, t.tm_min, t.tm_sec, ap.c_str());
  return String(buf);
}

void updateWeather() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey);
    int code = http.GET();
    if (code == 200) {
      String payload = http.getString();
      StaticJsonDocument<1024> doc;
      deserializeJson(doc, payload);
      temp = doc["main"]["temp"];
      hum = doc["main"]["humidity"];
      lastUpdated = getTime12();
    }
    http.end();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("Starting...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  lcd.clear();
  lcd.print("Ready");
  delay(1000);
}

void loop() {
  bool curState = digitalRead(BTN);
  if (lastState == HIGH && curState == LOW) {
    mode++;
    if (mode > 2) mode = 0;
    lcd.clear();
    delay(300);
  }
  lastState = curState;

  unsigned long now = millis();

  lcd.clear();

  if (mode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Time");
    lcd.setCursor(0, 1);
    lcd.print(getTime12());
  }

  if (mode == 1) {
    if (now - lastWeatherUpdate >= weatherInterval || lastWeatherUpdate == 0) {
      updateWeather();
      lastWeatherUpdate = now;
    }
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp);
    lcd.print("C H:");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Upd:");
    lcd.print(lastUpdated.substring(0,5));
  }


  if (pomodoroRun && now - prevMillis >= 1000) {
    prevMillis = now;
    pomodoroSec--;
    if (pomodoroSec < 0) {
      pomodoroSec = 59;
      pomodoroMin--;
    }
    if (pomodoroMin < 0) {
      pomodoroMin = 25;
      pomodoroSec = 0;
      pomodoroRun = false;
    }
  }

  if (mode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Pomodoro");
    lcd.setCursor(0, 1);
    if (pomodoroMin < 10) lcd.print("0");
    lcd.print(pomodoroMin);
    lcd.print(":");
    if (pomodoroSec < 10) lcd.print("0");
    lcd.print(pomodoroSec);
  }

  delay(500);
}
