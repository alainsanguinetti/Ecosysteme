#ifndef DISP_H
#define DISP_H

	#include "../src/struct.h"
	#include <SDL/SDL.h>
	#include <SDL/SDL_ttf.h>

	enum Disp_mode{
		TEXT,
		SDL
	};

	#define WINDOW_SIZE_X 900	// px
	#define WINDOW_SIZE_Y 900	// px
	#define COLOR_DEPTH 32	// bits
	#define VIDEO_OPTIONS SDL_HWSURFACE  //| SDL_NOFRAME	// loading in the video memory and no border nor title

	
	// When the user wants to display the field in the specified mode (SDL / text)
	void user_disp_field(Field * turf, SDL_Surface * screen, int mode);

	// Displays a field text mode
	void text_disp_field(Field * turf);

	// Displays a cell text mode
	void text_disp_pos(Field * turf, int x, int y);
	void text_disp_tile(Tile * cell);

	// Initializes the display
	SDL_Surface * init_sdl();
	
	// Pauses the display
	void disp_pause();
	
	// Displays a field, with SDL
	void sdl_disp_field(Field * turf, SDL_Surface * screen);
	
	// Displays a line of cell, with SDL
	void sdl_disp_line(Field * turf, SDL_Surface * screen, int i);
	
	// Displays a cell, with SDL
	void sdl_disp_cell(Field * turf, SDL_Surface * screen, int offset_y, int j);
	
	// Ends the display
	void quit_sdl();

#endif
