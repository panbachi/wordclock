#include <ESP8266WiFi.h>
#include "wifi.h"
#include <WiFiManager.h>

void Wifi::setup() {
  WiFi.hostname("WordClock-TEST");

  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock-TEST");
}

void Wifi::reset() {
  WiFi.disconnect(true);
}
