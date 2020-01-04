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

/*typedef struct {
  color_t color_bg;
  color_t color_fg;
  int timezone;
  bool dnd_active;
  clock_time_t dnd_start;
  clock_time_t dnd_end;
  String ntp;
} config_t;*/
#endif
