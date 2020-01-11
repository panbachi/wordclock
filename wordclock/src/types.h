#ifndef WORDCLOCK_TYPES_H
#define WORDCLOCK_TYPES_H

typedef struct { 
  int r;
  int g;
  int b;
} color_t;

typedef struct {
  int hour;
  int minute;
} clock_time_t;

#endif
