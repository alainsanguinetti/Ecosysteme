#ifndef DISP_H
#define DISP_H

#include "../src/struct.h"
#include <gtk/gtk.h>

// Run the application in graphics mode
void graphic_ecosysteme(Field * turf);

// Displays a field text mode
void text_disp_field(Field * turf);

// Displays a cell text mode
void text_disp_pos(Field * turf, int x, int y);
void text_disp_tile(Tile * cell);

#endif
