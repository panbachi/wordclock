#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FS.h>

#include "user_config.h"

#include "src/wifi.h"
#include "src/types.h"
#include "src/color.h"
#include "src/config.h"
#include "src/dnd.h"
#include "src/led.h"
#include "src/grid.h"
#include "src/time.h"
#include "src/httpServer.h"
#include "src/gui.h"
#include "src/controller.h"

void setup() {
  Serial.begin(74880);
  SPIFFS.begin();

  Config::load();

  Wifi::setup();  
  HttpServer::setup();

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(Led::ids, NUM_LEDS);
  FastLED.setBrightness(50);

  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i].setRGB(0, 0, 0);
  }

  FastLED.show();

  Time::setup();

  Grid::setTime(Time::hour, Time::minute);
}

void loop() {
  Time::loop();
  HttpServer::loop();
}
