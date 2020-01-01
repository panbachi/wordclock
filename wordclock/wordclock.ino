#include <utility>

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <FS.h>

#include "types.h"
#include "time.h"
#include "color.h"
#include "config.h"

#include "dnd.h"
#include "led.h"

#ifndef GRID_LANGUAGE
  #include "language/de-DE.h"
#else
  #define QUOTE(x) XQUOTE(x)
  #define XQUOTE(x) #x
  #define INCLUDE_FILE(x) QUOTE(language/x.h)
  #include INCLUDE_FILE(GRID_LANGUAGE)
#endif

void GUI_handleRootPath();
#include "server.h"
#include "gui.h"


String header;

void setup() {
  Serial.begin(74880);
  SPIFFS.begin();

  Config::load();

  WiFi.hostname("WordClock");

  WiFiManager wifiManager;
  wifiManager.autoConnect("WordClock");

  SERVER_setup();

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();

  TIME_setup();

  setTime(TIME_HOUR, TIME_MINUTE);
}

void loop() {
  TIME_loop();
  SERVER_loop();
}
