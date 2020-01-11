#ifndef WORDCLOCK_COLOR_H
#define WORDCLOCK_COLOR_H

#include <Arduino.h>

#include "types.h"

class Color {
  public:
    static color_t hexToRgb(String value);
    static String rgbToHex(const color_t& hex);
};

#endif
