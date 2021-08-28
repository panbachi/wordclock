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

  if (DATA_PIN != D4){
    // If we use a data pin different than d4, we will deactivate d4 because it triggers the blue board status led
    // I use D3 as data pin, because d4 is connected with the board led. 
    pinMode(D4, OUTPUT); // Define LED pin as output
    digitalWrite(D4, HIGH); // Switch the blue board status LED OFF
  }

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
