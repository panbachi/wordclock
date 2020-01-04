#ifndef WORDCLOCK_GRID_H
#define WORDCLOCK_GRID_H

#ifndef GRID_LANGUAGE
  #define de_DE
  #define GRID_LANGUAGE_STRING "de_DE"
  #include "language/de_DE.h"
  typedef class Grid_de_DE Grid;
#else
  #define QUOTE(x) XQUOTE(x)
  #define XQUOTE(x) #x
  #define INCLUDE_FILE(x) QUOTE(language/x.h)
  #define GRID_LANGUAGE_STRING QUOTE(x)
  #include INCLUDE_FILE(GRID_LANGUAGE)
  
  #define YYC() Grid_
  #define YYT(x) typedef class YYC()x Grid;
  YYT(GRID_LANGUAGE)
#endif

#if 0
class Grid {
	public:
		static void setTime(int hour, int minute);
};
#endif

#endif