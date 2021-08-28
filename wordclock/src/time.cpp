#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>

#include "time.h"
#include "grid.h"
#include "utcOffset.h"


void Time::setup() {

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    delay(1000);
  } else if (!rtc.begin()) {
    Serial.println("Couldn't find RTC (2nd try)");
  }

  Time::ntpClient.begin();
  Time::ntpClient.update();
}

void Time::loop() {
  DateTime now = rtc.now();
  int h = now.hour();
  int m = now.minute();

  if (Time::ntpClient.update()) {
    h = Time::ntpClient.getHours();
    m = Time::ntpClient.getMinutes();
    rtc.adjust(DateTime(Time::ntpClient.getEpochTime()));
  }
  Time::ntpClient.update();

  if(m != Time::minute) {
    if(m == 0 && h == Time::hour) {
      h = (h + 1) % 24;
    }

    Time::hour = h;
    Time::minute = m;
    Grid::setTime(Time::hour, Time::minute);

    if (Config::automatic_timezone) {
      UtcOffset::updateLocalizedUtcOffset();
      Time::ntpClient.setTimeOffset(Config::timezone);
    }
  }
}

int Time::hour = -1;
int Time::minute = -1;
RTC_DS1307 Time::rtc;
WiFiUDP Time::udp;
NTPClient Time::ntpClient = NTPClient(Time::udp);
