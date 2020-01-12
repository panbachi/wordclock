#ifndef WORDCLOCK_GRID_LANG_DE_DE_H
#define WORDCLOCK_GRID_LANG_DE_DE_H

class Grid_de_DE {
	public:
	static int time_it_is[5];
	static int time_minutes[12][12];
	static int time_hours[12][6];

	static void setTime(int hour, int minute);
};

typedef class Grid_de_DE Grid;

#endif
