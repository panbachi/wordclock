#include <Homie.h>
#include <FastLED.h>
#include <NTPClient.h>

#define NUM_LEDS 121
#define DATA_PIN D4

CRGB leds[NUM_LEDS];
int r = 255;
int g = 255;
int b = 255;
int offset = 0;
int hour = -1;
int minute = -1;

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", offset, 3600000);

HomieNode colorNode("color", "color");
HomieNode offsetNode("offset", "offset");

boolean colorHandler(const HomieRange& range, const String& value) {
  int number = (int) strtol( value.c_str(), NULL, 16);
  
  // Split them up into r, g, b values
  r = number >> 16;
  g = number >> 8 & 0xFF;
  b = number & 0xFF;
  
  return true;
}

boolean offsetHandler(const HomieRange& range, const String& value) {
  timeClient.setTimeOffset(value.toInt() * 3600);
  
  return true;
}

void setTime(int hour, int minute) {
  int it_is[] = {110, 111, 113, 114, 115};
  
  int minutes[][12] = {
    { 13,  12,  11,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
    {117, 118, 119, 120,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
    {109, 108, 107, 106,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
    { 92,  93,  94,  95,  96,  97,  98,  85,  84,  83,  82,  -1},
    {105, 104, 103, 102, 101, 100,  99,  85,  84,  83,  82,  -1},
    {117, 118, 119, 120,  81,  80,  79,  66,  67,  68,  69,  -1},
    { 66,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
    {117, 118, 119, 120,  85,  84,  83,  82,  66,  67,  68,  69},
    {105, 104, 103, 102, 101, 100,  99,  81,  80,  79,  -1,  -1},
    { 92,  93,  94,  95,  96,  97,  98,  81,  80,  79,  -1,  -1},
    {109, 108, 107, 106,  81,  80,  79,  -1,  -1,  -1,  -1,  -1},
    {117, 118, 119, 120,  81,  80,  79,  -1,  -1,  -1,  -1,  -1}
  };

  int hours[][6] = {
    {71, 72, 73, 74, 75, -1},
    {63, 62, 61, 60, -1, -1},
    {65, 64, 63, 62, -1, -1},
    {45, 46, 47, 48, -1, -1},
    {36, 35, 34, 33, -1, -1},
    {51, 52, 53, 54, -1, -1},
    {20, 19, 18, 17, 16, -1},
    {60, 59, 58, 57, 56, 55},
    {23, 24, 25, 26, -1, -1},
    {40, 39, 38, 37, -1, -1},
    {27, 28, 29, 30, -1, -1},
    {43, 42, 41, -1, -1, -1}
  };
  
  minute = (minute - (minute % 5));
  
  if(minute >= 25) {
    hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  // RESET
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }
  
  // ES IST
  for(int i = 0; i < 5; i++) {
    leds[it_is[i]].setRGB(r,g,b);
  }

  // MINUTES
  for(int m = 0; m < 12; m++) {
    if(minutes[minute][m] >= 0) {
      leds[minutes[minute][m]].setRGB(r,g,b);
    }
  }

  // HOURS
  for(int h = 0; h < 6; h++) {
    if(hours[hour][h] >= 0) {
      if(hour == 1 && minute == 0 && h == 3) {
      } else {
        leds[hours[hour][h]].setRGB(r,g,b);
      }
    }
  }

  FastLED.show();
}

void loopHandler() {
  timeClient.update();
  
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();

  if(h != hour || m != minute) {
    setTime(h, m);
    hour = h;
    minute = m;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( 40 );

  Homie_setBrand("wordclock");
  Homie_setFirmware("Panbachi WordClock", "1.1.0");

  colorNode.advertise("color").settable(colorHandler);
  offsetNode.advertise("offset").settable(offsetHandler);
  Homie.setLoopFunction(loopHandler);

  timeClient.begin();
  timeClient.update();

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0, 0, 0);
  }

  FastLED.show();

  Homie.setup();
  
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
}

void loop() {
  Homie.loop();
}
