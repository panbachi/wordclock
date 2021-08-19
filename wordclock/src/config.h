#ifndef WORDCLOCK_CONFIG_H
#define WORDCLOCK_CONFIG_H

#include <Arduino.h>

#include "../user_config.h"
#include "types.h"

/***********************************************
 * CONFIG START
 **********************************************/

/* Grid rows
 *
 * Options
 * -------
 * 10: 10 rows
 * 11: 11 rows
 */
#ifndef GRID_ROWS
  #define GRID_ROWS 11
#endif

/* Grid cols
 *
 * Options
 * -------
 * 11: 11 cols
 */
#ifndef GRID_COLS
  #define GRID_COLS 11
#endif

/* Postition of first LED
 *
 * Options
 * -------
 * 0: top-left
 * 1: top-right
 * 2: buttom-left
 * 3: buttom-right
 */
#ifndef GRID_FIRST
  #define GRID_FIRST 2
#endif

/* Grid language
 *
 * Options
 * -------
 * 1: de-DE:     german
 * 2: de-DE_alt: german alternative
 * 3: de_DE_s: "Es ist" only at full and half hour
 * 4: de_DE_s1: "Es ist" only at full and half hour + Minutes in Last row (new front Plate De_de_S1)
 */
#ifndef GRID_LANGUAGE
  #define GRID_LANGUAGE de_DE
//#define GRID_LANGUAGE de_DE_alt
#endif

/* Position of single minute LEDs
 *
 * Options
 * -------
 * 0: before
 * 1: after
 */
#ifndef GRID_SINGLE_MINUTES
  #define GRID_SINGLE_MINUTES 1
#endif

#ifndef EXTRA_LEDS
  #define EXTRA_LEDS 4
#endif

/* Data PIN, where the LED strip is connected to */
#ifndef DATA_PIN
  #define DATA_PIN D4
#endif

#ifndef CONSUMPTION_D1_MINI
  #define CONSUMPTION_D1_MINI 170 // 170mA in active mode
#endif

#ifndef CONSUMPTION_PER_LED
  #define CONSUMPTION_PER_LED 60 // 60mA per LED on full brightness in white.
#endif

/***********************************************
 * CONFIG END
 **********************************************/

class Config {
  public:
    static color_t color_bg;
    static color_t color_fg;
    static int power_supply;
    static double brightness;
    static bool automatic_timezone;
    static int timezone;
    static bool dnd_active;
    static clock_time_t dnd_start;
    static clock_time_t dnd_end;
    static String ntp;
    static bool healthcheck;

    static void save();
    static void load();
};
#endif
