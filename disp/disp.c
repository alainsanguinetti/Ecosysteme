#include "./disp.h"
#include ".././src/days.h"

static TTF_Font * font = NULL;
static SDL_Surface * cell = NULL;
	SDL_Color black = {0, 0, 0, 255};
	SDL_Color red = {255, 0, 0, 255};
	SDL_Color yellow = {255, 255, 0, 255};

// When the user wants to display the field in the specified mode (SDL / text)
void user_disp_field(Field * turf, SDL_Surface * screen, int mode){
	int repeat_disp = 1;
	
	while(repeat_disp){
		if(mode == TEXT){
			// The user wants text display
			text_disp_field(turf);
		}else if (mode == SDL && screen != NULL){
			// The user would like beautiful SDL display
			sdl_disp_field(turf, screen);
		}
		
		// Now we ask before quiting
		printf("Quit display ?\t 0:yes, 1:no\n");
		scanf("%d", &repeat_disp);
	};
}

void text_disp_field(Field * turf){
	int i = 0;
	int j = 0;
	
	printf("This field is of size : %d x %d\n", turf->m, turf->n);
	
	for(i = 0; i < turf->m; i++){
		for(j = 0; j < turf->n; j++){
			text_disp_pos(turf, i, j);
		}
	}
}


void text_disp_pos(Field * turf, int x, int y){
	printf("Displaying tile at position x = %d, y = %d", x, y);
	text_disp_tile(turf->array[x][y]);
}


void text_disp_tile(Tile * cell){
	printf("\tGrass : %d \t", cell->qty_grass);
	if(cell->animals == NULL){
		printf("No animal\n");
	}else{
		printf("Specie : %d\n", cell->animals->specie);
	}
}


// Initializes the display
SDL_Surface * init_sdl(){
	SDL_Surface * new_display = NULL;
	
	// SDL initialization, use of only the VIDEO part
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
   
    // This is for text display
	TTF_Init();

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
    
    // Setting of the new window
    new_display = SDL_SetVideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, COLOR_DEPTH, VIDEO_OPTIONS);
    if (new_display == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
	SDL_WM_SetCaption("Proies - Prédateurs", NULL);
	
	// One cell
	if(!cell){
		cell = SDL_CreateRGBSurface(SDL_HWSURFACE, (WINDOW_SIZE_X / TURF_M), (WINDOW_SIZE_Y / TURF_N), COLOR_DEPTH, 0, 0, 0, 0);
		SDL_FillRect(cell, NULL, SDL_MapRGB(new_display->format, 17, 206, 112));
	}
    
	return new_display;
}


// Pauses the display
void disp_pause(){
	int pause = 1;
    SDL_Event event;
 
    while (pause)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                pause = 0;
        }
	}
}


// Displays the state of the field
void sdl_disp_field(Field * turf, SDL_Surface * screen){
	int i;
	
	printf("This field is of size : %d x %d\n", turf->m, turf->n);
	
	// Initializes TTF_Font
	if(!font){
		font = TTF_OpenFont("./disp/font/Sansation_Bold.ttf", FONT_SIZE);
	}

	if(font == NULL){
		printf("sdl_disp_field : TTF_font not initialized\n");
		
		exit(EXIT_FAILURE);
	}
	
	// Blank the window
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 120, 120, 120));
	
	// For every line of the field, display it
	for(i = 0; i < turf->n; i++){
		sdl_disp_line(turf, screen, i, font);
	}
	
	// Update the window
	SDL_Flip(screen);

	// Leave it like this
}

// Displays a line of cell, with SDL
void sdl_disp_line(Field * turf, SDL_Surface * screen, int i, TTF_Font * font){
	//printf("Displaying line %d\n", i);
	
	int j;
	
	// Calculates the offset
	int offset = i * (WINDOW_SIZE_Y / turf->n);
	
	// For every cell of the line, display it
	for(j = 0; j < turf->m; j++){
		sdl_disp_cell(turf, screen, offset, i, j, font);
	}
}

// Displays a cell, with SDL
void sdl_disp_cell(Field * turf, SDL_Surface * screen, int offset_y, int i, int j, TTF_Font * font){
	
	//printf("Displaying cell %d, %d\n", i, j);
	char text_cell[50];			// The text to be written
	SDL_Surface * text = NULL;	// The surface containing the text to write on the cell
	SDL_Color color;
	
	// Calculates the x offset	
	int offset_x = j * (WINDOW_SIZE_X / turf->m);
	
	// Add a green rectangle to represent grass
	
	// This is the green rectangle position
	SDL_Rect position;
	position.x = offset_x;
	position.y = offset_y;
	
	// We add the green rectangle
	SDL_BlitSurface(cell, NULL, screen, &position);
	
	/* Write text for the cell */
		/* About the grass */
		sprintf(text_cell, "Grss : %d", turf->array[i][j]->qty_grass);
		text = TTF_RenderText_Solid(font, text_cell, black);
		position.x+=10;
		position.y+=10;
		SDL_BlitSurface(text, NULL, screen, &position);

		/* About the animal */
		if(turf->array[i][j]->animals == NULL){
			 //sprintf(text_cell, "None");
		}else{
			/* The color depends on the first digit of the class of the animal */
			if(turf->array[i][j]->animals->specie == 2){
				color = red;
			}else{
				color = yellow;
			}
			
			sprintf(text_cell, "Spc : %d", turf->array[i][j]->animals->specie);
			text = TTF_RenderText_Solid(font, text_cell, color);
			position.y+=FONT_SIZE;
			SDL_BlitSurface(text, NULL, screen, &position);
		}
		
	SDL_FreeSurface(text);
	
}


// Ends the display
void quit_sdl(){
	
	// Close cell
	SDL_FreeSurface(cell);
	
	// Close font
	TTF_CloseFont(font);
	
	// End of TTF
	TTF_Quit();
	
	// End of use of SDL
	SDL_Quit();	
}
