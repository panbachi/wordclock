#ifndef WORDCLOCK_GRID_H
#define WORDCLOCK_GRID_H

#include "../user_config.h"
#include "config.h"

#ifdef GRID_LANGUAGE
  #define QUOTE(x) XQUOTE(x)
  #define XQUOTE(x) #x
  #define INCLUDE_FILE(x) QUOTE(language/x.h)
  #include INCLUDE_FILE(GRID_LANGUAGE)
#endif

#endif