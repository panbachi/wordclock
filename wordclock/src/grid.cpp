#include <Arduino.h>
#include "grid.h"
#include "../user_config.h"
#include "config.h"

#ifndef QOUTE
	#define QUOTE(x) XQUOTE(x)
	#define XQUOTE(x) #x
#endif

void Grid::setTime(int hour, int minute) {
	if(GRID_LANGUAGE_STRING == "de_DE") {
		#include "language/de_DE.h"
		Grid_de_DE::setTime(hour, minute);
	} else if(GRID_LANGUAGE_STRING == "de_DE_alt") {
		#include "language/de_DE_alt.h"
		Grid_de_DE_alt::setTime(hour, minute);
	} else {
		Serial.println(GRID_LANGUAGE_STRING);
	}
}