#include <ncurses.h>
#include "input_layer.h"
#include "canvas.h"


static int get_event(MEVENT*, int);
static int get_clickpos(Coord*);


void update_input(int i) {
	Sprite* sprite = &INPUT_CANVAS.sprites[i];
	if (sprite->active) return;

    Coord click_pos;
    if (get_clickpos(&click_pos) == OK) {
        sprite->path.current = click_pos;
		sprite->view = 'X';
		sprite->active = true;
	}

}


void init_input() {
	INPUT_CANVAS.window = newwin(0, 0, 0, 0);
	keypad(INPUT_CANVAS.window, true); // Allows input from all keys. Includes mouse.
	mousemask(BUTTON1_CLICKED, NULL); // Listen for mouse events
	nodelay(INPUT_CANVAS.window, true);

	mouseinterval(35);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	wattron(INPUT_CANVAS.window, COLOR_PAIR(1));
}


static int get_event(MEVENT* event, int event_type) {
	int status = ERR;
	int c = wgetch(INPUT_CANVAS.window);
	if (c == KEY_MOUSE && getmouse(event) == OK) {
		status = (event->bstate & event_type) ? OK : ERR; // Check if it's the right event
	}
	return status;
}


static int get_clickpos(Coord* coord) {
	MEVENT event;

	int status = get_event(&event, BUTTON1_CLICKED);
	if (status == OK) {
		coord->x = event.x;
		coord->y = event.y;
	}
	return status;
}
