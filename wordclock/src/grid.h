#ifndef WORDCLOCK_GRID_H
#define WORDCLOCK_GRID_H

#include "../user_config.h"
#include "config.h"

#ifndef GRID_LANGUAGE
  #define de_DE
  #define GRID_LANGUAGE_STRING "de_DE"
  //#include "language/de_DE.h"
#else
  #define QUOTE(x) XQUOTE(x)
  #define XQUOTE(x) #x
  #define INCLUDE_FILE(x) QUOTE(language/x.h)
  #define GRID_LANGUAGE_STRING QUOTE(x)
  #include INCLUDE_FILE(GRID_LANGUAGE)
#endif

#if 0
class Grid {
	public:
		static void setTime(int hour, int minute);
};
#endif

#endif