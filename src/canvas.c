#include "canvas.h"
#include "main.h"
#include "animate.h"

#include "collision_layer.h"
#include "alien_layer.h"
#include "input_layer.h"
#include "defense_layer.h"


static void draw(Canvas*, Coord*, chtype);


void clear_sprite(Canvas* canvas, Sprite* sprite) {
    if (sprite->view == ' ')
        return;

    Coord box[8];
    Sprite gc = { .view = ' ' };
    set_animation(&gc, &sprite->path.beg, &sprite->path.current, 10000);

    // Increment the end one further.
    int dx = gc.path.end.x - gc.path.beg.x;
    int dy = gc.path.end.y - gc.path.beg.y;
    gc.path.end.x += (dx) ? dx / abs(dx) : 0;
    gc.path.end.y += (dy) ? dy / abs(dy) : 0;

    while (!is_animation_done(&gc)) {
        get_box(&gc.path.current, 1, &box);
        for (int b = 0; b < 8; b++) {
            mvwaddch(canvas->window, box[b].y, box[b].x, gc.view);
        }

        update_animation(canvas, &gc);
        wrefresh(canvas->window);
    }
}


void draw_sprite(Canvas* canvas, Sprite* sprite) {
    draw(canvas, &sprite->path.current, sprite->view);
}


bool has_object(Canvas* canvas, Coord* coord) {
    char c = mvwinch(canvas->window, coord->y, coord->x);
    return (c != ERR && c != ' ');
}


static void draw(Canvas* canvas, Coord* point, chtype c) {
    mvwaddch(canvas->window, point->y, point->x, c);
}