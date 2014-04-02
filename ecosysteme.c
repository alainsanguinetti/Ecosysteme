#include "./src/days.h"
#include "./disp/disp.h"

int main(int argc, char *argv[])
{
	bool running = false;
	
	// Two verbosity levels
	myPrintf[QUIET] = quietprint;
	myPrintf[VERBOSE] = printf;
	
	// Before continuing, read the arguments
	running = readArguments( argc, argv );

	// If the arguments are correct, start a simulation
	while ( running ) {
		myPrintf[ verbosemode ] ( "main : running is true\n" );

		// Init graphics
		SDL_Surface * screen = NULL;
		screen = init_sdl();

		// Simulates
		simulation ( screen );

		// End of graphics
		SDL_FreeSurface(screen);
		quit_sdl();

		// Quit running mode
		running = false;
	};

	return 0;
}
