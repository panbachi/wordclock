#include <FastLED.h>
#define NUM_LEDS 121
#define DATA_PIN D4

CRGB leds[NUM_LEDS];
    
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( 40 );

}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::Red; 
      FastLED.show();
      delay(100);
      
      leds[led] = CRGB::Black;
      FastLED.show();
      delay(100);
    }

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::White; 
      
    }
    FastLED.show();
    delay(5000);

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::Black; 
      
    }

    FastLED.show();
}
