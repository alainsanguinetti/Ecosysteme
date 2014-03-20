#include "./src/days.h"
#include "./disp/disp.h"

int main()
{
	int nb_days;

	// Init graphics
	SDL_Surface * screen = NULL;
	screen = init_sdl();

	Field * Test = createField(TURF_M, TURF_N);
	Characteristics * test = initCharacteristics(2);
	Test->species = test;

	printf("Enter the number of days : ");
	scanf("%d", &nb_days);

	advanced_field_initialization ( Test, test );
	days_simulation ( nb_days, Test, screen );

	deleteCharacteristics(test);

	deleteField(Test);

	// End of graphics
	SDL_FreeSurface(screen);
	quit_sdl();

	return 0;
}
