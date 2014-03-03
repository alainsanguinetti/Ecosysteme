#include "./src/days.h"
#include "./disp/disp.h"

int main()
{
	// Init graphics
	SDL_Surface * screen = NULL;
	screen = init_sdl();
	
	Field * Test = createField(3,3);
	int is_ok = 1;
	
	Characteristics * test = initCharacteristics(2);
	
	printf("%d\n", test->array[0][0]);
	
	// Creates an animal
	Animal * anitest = createAnimal(130,test);
	printf("%d\n", anitest->class);
	
	// Puts this animal at tile (0,1)
	is_ok = addAnimal(anitest, Test->array[0][1]);
	
	text_disp_field(Test);
	
	//user_disp_field(Test, screen, SDL);
	
	deleteCharacteristics(test);
	
	deleteField(Test);
	
	// End of graphics
	SDL_FreeSurface(screen);
	quit_sdl();

	return 0;
}


