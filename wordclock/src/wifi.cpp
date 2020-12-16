#include <ESP8266WiFi.h>
#include <WiFiManager.h>

#include "wifi.h"

void Wifi::setup() {
  WiFi.hostname("WordClock");
  WiFi.mode(WIFI_STA);

  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock");
}

void Wifi::reset() {
  WiFi.disconnect(true);
}
