#include <FastLED.h>
#include "led.h"
#include "config.h"

int Led::getLedId(int id) { 
  int col = id % GRID_COLS;
  int row = (floor)(id / GRID_COLS);
  int led = 0;
  
  if(GRID_FIRST == 3) {        
    led = (row % 2 != GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 2) {
    led = (row % 2 == GRID_ROWS % 2) ? (GRID_ROWS - row) * GRID_COLS - 1 - col : (GRID_ROWS - row - 1) * GRID_COLS + col;
  } else if(GRID_FIRST == 1) {
    led = (row % 2 == 0) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  } else if(GRID_FIRST == 0) {
    led = (row % 2 == 1) ? ((row * GRID_COLS) + col) : ((row + 1) * GRID_COLS) - col - 1;
  }

  if(GRID_SINGLE_MINUTES == 0) {
    led += 4;
  }

  return led;
}

void Led::setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(Led::ids, NUM_LEDS);
  FastLED.setBrightness(50);

  for(int i = 0; i < NUM_LEDS; i++) {
    Led::ids[i].setRGB(0, 0, 0);
  }

  FastLED.show();
}

CRGB Led::ids[NUM_LEDS];
