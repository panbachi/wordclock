#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "time.h"
#include "grid.h"
#include "utcOffset.h"

void Time::setup() {
  Time::ntpClient.begin();
  Time::ntpClient.update();
}

void Time::loop() {
  Time::ntpClient.update();

  int h = Time::ntpClient.getHours();
  int m = Time::ntpClient.getMinutes();

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
WiFiUDP Time::udp;
NTPClient Time::ntpClient = NTPClient(Time::udp);
