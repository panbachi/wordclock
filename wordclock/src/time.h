#ifndef WORDCLOCK_TIME_H
#define WORDCLOCK_TIME_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>

class Time {
  public:
    static int hour;
    static int minute;
    static WiFiUDP udp;
    static NTPClient ntpClient;
    static RTC_DS1307 rtc;

    static void setup();

    static void loop();
};

#endif
