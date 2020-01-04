#include <Arduino.h>
#include "grid.h"
#include "../user_config.h"
#include "config.h"

#ifndef QOUTE
	#define QUOTE(x) XQUOTE(x)
	#define XQUOTE(x) #x
#endif

#if 0
void Grid::setTime(int hour, int minute) {
	if(GRID_LANGUAGE_STRING == "de_DE") {
		Grid_de_DE::setTime(hour, minute);
	} else if(GRID_LANGUAGE_STRING == "de_DE_alt") {
		Grid_de_DE_alt::setTime(hour, minute);
	} else {
		Serial.println(GRID_LANGUAGE_STRING);
	}
}
#endif