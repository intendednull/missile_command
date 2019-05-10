#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "mainloop.h"
#include "canvas.h"
#include "input_layer.h"
#include "alien_layer.h"
#include "defense_layer.h"
#include "collision_layer.h"


void init() {
	srand(time(NULL)); // seed for random events.
	initscr();
    noecho(); // Don't echo input.
    start_color(); // Enable colored formatting.
	curs_set(0); // Invisible cursor

	init_input();
	init_alien();
	init_defense();
	init_collision();
	init_garbage_collector();
}

void update() {
	static Canvas* layers[] = {
		&INPUT_CANVAS,
		&ALIEN_CANVAS,
		&DEFENSE_CANVAS,
		&COLLISION_CANVAS,
		&GARBAGE_COLLECTOR_CANVAS
	};
	for (int i = 0; i < 120; i++) {
		update_input(i);
		update_alien(i);
		update_defense(i);
		update_collision(i);

		for (int l = 0; l < 5; l++) {
			Canvas* layer = layers[l];
			Sprite* sprite = &layer->sprites[i];

			if (sprite->alive) {
				update_animation(layer, sprite);
			}
			// else if (has_object(layer, &sprite->path.current)) {
			// 	clear_sprite(sprite, 80);
			// }
		}
	}
	wrefresh(INPUT_CANVAS.window);
	wrefresh(ALIEN_CANVAS.window);
	wrefresh(DEFENSE_CANVAS.window);
	wrefresh(COLLISION_CANVAS.window);
	wrefresh(GARBAGE_COLLECTOR_CANVAS.window);
	refresh();
}


void teardown() {
	endwin();
}

void panic(char* str) {
	teardown();
	printf("Error: %s\n", str);
	exit(0);
}

void mainloop() {
	init();

    bool running = true;
    while (running) {
		update();
	}
	teardown();
}
