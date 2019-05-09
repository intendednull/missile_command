#include <time.h>
#include <stdlib.h>
#include "alien_layer.h"
#include "canvas.h"
#include "animate.h"
#include "collision_layer.h"



void init_alien() {
    ALIEN_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    wattron(ALIEN_CANVAS.window, COLOR_PAIR(2));
}


void update_alien(int i) {
	Sprite* sprite = &ALIEN_CANVAS.sprites[i];

    static long last_deploy;
    static int missile_count = 100;
    static int rate_limit = 2;

    bool ready = ((get_nanotime() - last_deploy) / SECOND >= rate_limit);

    if (!sprite->active && ready && missile_count) {
        Coord start = { .x = rand() % COLS, .y = 1 };
        Coord target = { .x = start.x, .y = LINES };

        set_animation(sprite, &start, &target);
        sprite->view = ACS_DIAMOND;
        sprite->active = 2;
        sprite->path.speed = 6;

        last_deploy = get_nanotime();
        --missile_count;
    }
}
