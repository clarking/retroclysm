
//  Main Loop for RetroClysm

#include <ncurses.h>
#include <ctime>
#include "game.h"

void do_colors();
//void load_items();

int main(int argc, char *argv[]) {

	srand(time(nullptr));
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);
	do_colors();
	curs_set(0);

	rand();
	game g;
	while (!g.do_turn());
	erase();
	endwin();
	system("clear");
	return 0;
}

#define HILIGHT COLOR_BLUE

void do_colors() {
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);

	// Inverted Colors
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
	init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(14, COLOR_BLACK, COLOR_YELLOW);

	// Highlighted - blue background
	init_pair(15, COLOR_WHITE, HILIGHT);
	init_pair(16, COLOR_RED, HILIGHT);
	init_pair(17, COLOR_GREEN, HILIGHT);
	init_pair(18, COLOR_BLUE, HILIGHT);
	init_pair(19, COLOR_CYAN, HILIGHT);
	init_pair(20, COLOR_BLACK, HILIGHT);
	init_pair(21, COLOR_MAGENTA, HILIGHT);
	init_pair(22, COLOR_YELLOW, HILIGHT);

	init_pair(23, COLOR_BLACK, COLOR_BLACK);
}
