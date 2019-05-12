#include "defense_layer.h"
#include "input_layer.h"
#include "animate.h"
#include "collision_layer.h"

static const int defense_arsenal = 10;
static struct Base* get_launchpoint(Coord*);

void init_defense() {
    DEFENSE_CANVAS.window = newwin(0, 0, 0, 0);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wattron(DEFENSE_CANVAS.window, COLOR_PAIR(3));

    int buff = (int) ((double) COLS) * 0.8 / 2;
    BASE_LEFT.position.x = buff / 2;
    BASE_MID.position.x = COLS / 2;
    BASE_RIGHT.position.x = COLS - buff / 2;

    BASE_LEFT.position.y = LINES;
    BASE_MID.position.y = LINES;
    BASE_RIGHT.position.y = LINES;
    reset_defense();
}


void reset_defense() {
    BASE_LEFT.missile_count = defense_arsenal;
    BASE_MID.missile_count = defense_arsenal;
    BASE_RIGHT.missile_count = defense_arsenal;
}


void update_defense(int i) {
    Sprite* target = &INPUT_CANVAS.sprites[i];
    if (!target->alive)
        return;

    Sprite* missile = &DEFENSE_CANVAS.sprites[i];
    if (!missile->alive) {
        struct Base* base = get_launchpoint(&target->path.current);
        if (base) {
            set_animation(missile, &base->position, &target->path.current, 80);
            missile->view = ACS_DIAMOND;
            missile->keep_alive = SECOND * .5;
            --base->missile_count;
        }

    } else if (cmp_eq(&missile->path.current, &missile->path.end)) {
        collide_input_defense(&missile->path.current);
        target->alive = 0;
    }
}


static struct Base* get_launchpoint(Coord* target) {
    struct Base* bases[] = {&BASE_LEFT, &BASE_MID, &BASE_RIGHT};
    struct Base* base = NULL;
    for (int i = 0; i < 3; i++) {
        if (!bases[i]->missile_count)
            continue;

        if (base) {
            double dist_curr = distance(&base->position, target);
            double dist_next = distance(&bases[i]->position, target);
            if (dist_next < dist_curr)
                base = bases[i];

        } else
            base = bases[i];
    }

    return base;
}