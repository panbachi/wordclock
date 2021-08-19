#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "src/grid.h"
#include "src/wifi.h"
#include "src/types.h"
#include "src/color.h"
#include "src/config.h"
#include "src/dnd.h"
#include "src/led.h"
#include "src/time.h"
#include "src/httpServer.h"
#include "src/gui.h"
#include "src/controller.h"
#include "src/healthcheck.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  SPIFFS.begin();

  Config::load();

  Wifi::setup();
  HttpServer::setup();
  Led::setup();
  Time::setup();

  Grid::setTime(Time::hour, Time::minute);
  
  if (Config::healthcheck ){
    // run simple LED check at start (uncomment to deactivate)
    Healthcheck::run();
  }
}

void loop() {
  Time::loop();
  HttpServer::loop();
}
