#ifndef DAYS_H
	#define DAYS_H
	
	#include "struct.h"
	#include <time.h>

	#define PUBERTY 2

	// Set the initial state of the field
	void initial_state (Field *turf, Characteristics * species);
	//Moves Preys and Predators
	void Move_Bitch_GetOut_The_Way(Field *turf);
	// Frames the simulation : simulates nb_days days
	void days_simulation(int nb_days, Field * turf);
	// Simulates a day
	void day_simulation(Field * turf);
	// Make grass grow everywhere on the field
	void The_Grass_Is_Greener_When_You_Water_It(Field *turf);
	//Make predators eat preys if possible
	void Eat_Dat_Motherfudger(Field *turf); 
	//Make preys eat grass if possible
	void Shave_Dat_Grass(Field *turf);
	// make preys and predators grow old
	void Time_Is_A_Bitch(Field *turf);
	//Allow predators or preys to reproduce
	void Sexy_Time(Field *turf);
#endif
