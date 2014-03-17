#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct animal Animal;
struct animal {
	int class;			// first digit : specie, second digit : age, third digit : mutation/subspecie !
	int moves_radius;
	int eat;			// Number of lower rank animals eaten by day
	int dies_after;		// Number of fasting days in a row allowed
};

typedef struct tile {
	int qty_grass;
	Animal * animals;
} Tile;

#define NB_CHARACTERISTICS 4
typedef struct characteristics {
	int m; // Number of different classes
	int ** array;	// Relations between class and the other characteristics
} Characteristics;

typedef struct field {
	Characteristics * species;
	Tile *** array;
	int m;
	int n;
} Field;

// Creates a field of size m * n
Field * createField(int m, int n);

// Creates an array of characteristics for n diff species
Characteristics * initCharacteristics(int n);

// Allocate an animal of class "class" according to the characteristics defined in species
Animal * createAnimal(int class, Characteristics * species);

// This places the animal "this_animal" at the place defined by "that_place". Returns 1 in case of success.
int addAnimal(Animal * this_animal, Tile * that_place);

// Remove an animal of class "class" from that place
Animal * removeAnimal(int class, Tile * that_place);

// Moves this animal from position x y to position next_x, next_y on field "turf". Returns 1 in case of success
int moveAnimal(int class, int x, int y, int next_x, int next_y, Field * turf);

// Counts the animals
void countAnimals(Field * turf);

// Functions to delete the structures
void deleteCharacteristics(Characteristics * my_charact);

void deleteAnimal(Animal * my_animal);

void deleteTile(Tile * my_tile);

void deleteField(Field * turf);

#endif


