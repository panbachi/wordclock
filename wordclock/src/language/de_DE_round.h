#ifndef WORDCLOCK_GRID_LANG_DE_DE_ROUND_H
#define WORDCLOCK_GRID_LANG_DE_DE_ROUND_H

#ifndef EXTRA_LEDS
  #define EXTRA_LEDS 4
#endif

class Grid_de_DE_round {
	public:
	static int time_it_is[5];
	static int time_minutes[12][12];
	static int time_hours[12][6];

	static void setTime(int hour, int minute);
};

typedef class Grid_de_DE_round Grid;

#endif
