#include <Arduino.h>

#include "healthcheck.h"
#include "config.h"
#include "led.h"

void Healthcheck::run() {
  FastLED.setBrightness(Config::brightness * 255);
  for(int i = 0; i < NUM_LEDS; i++) {
	Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }
  FastLED.show();

  for(int i = 0; i < NUM_LEDS; i++) {
      Led::ids[i].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
      FastLED.show();
      delay(25);
      
      Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
    }
    FastLED.setBrightness(Config::brightness * 255);
  
  for(int i = 0; i < NUM_LEDS; i++) {
	Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }
  FastLED.show();
}
