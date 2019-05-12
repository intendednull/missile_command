#ifndef ANIMATE_H
#define ANIMATE_H

#include <ncurses.h>
#include "canvas.h"

#define SECOND 1000000000L


void lerp(Vector*);
void set_animation(Sprite*, Coord*, Coord*, int);
void update_animation(Canvas*, Sprite*);
double distance(Coord*, Coord*);
double slope(Coord*, Coord*);
bool cmp_eq(Coord*, Coord*);
bool cmp_gt(Coord*, Coord*);
bool is_animation_done(Sprite*);
unsigned long get_nanotime();



#endif