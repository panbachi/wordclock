#ifndef WORDCLOCK_LED_H
#define WORDCLOCK_LED_H

#include <FastLED.h>

#define NUM_LEDS ((GRID_ROWS * GRID_COLS) + 4)

class Led {
  public:
    static CRGB ids[];

    static int getLedId(int id);
    static void setup();
    static double getMaxBrightnessPercnt();
    static int getMaxNumberIlluminatedLeds();
};

#endif
