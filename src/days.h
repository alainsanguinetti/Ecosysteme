#ifndef DAYS_H
#define DAYS_H

#include "struct.h"

// Set the initial state of the field
void initial_state (Field *turf, Characteristics * species);
// Frames the simulation : simulates nb_days days
void days_simulation(nb_days);
// Simulates a day
void day_simulation(Field * turf);
// Make grass grow everywhere on the field

// Randomly moves predators or preys first

// 
#endif
