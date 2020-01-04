#ifndef GRID_LANGUAGE
  #include "language/de_DE.h"
#else
  #define QUOTE(x) XQUOTE(x)
  #define XQUOTE(x) #x
  #define INCLUDE_FILE(x) QUOTE(language/x.h)
  #include INCLUDE_FILE(GRID_LANGUAGE)
  //#define GRID_CLASSNAME "Grid_"
  //#define Grid GRID_CLASSNAME QUOTE(GRID_LANGUAGE)
#endif
