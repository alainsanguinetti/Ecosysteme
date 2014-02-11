#ifndef STRUCT
#define STRUCT


#include <stdio.h>
#include <stdlib.h>

typedef struct animal Animal;
struct animal {
	int class;			// first digit : specie, second digit : age, third digit : mutation/subspecie !
	int moves_radius;
	int eat;			// Number of lower rank animals eaten by day
	int dies_after;		// Number of fasting days in a row allowed
	Animal * next_animal;
};

typedef struct tile {
	int qty_grass;
	Animal * animals;
} Tile;

typedef struct field {
	Tile *** array;
	int n;
	int m;
} Field;

#define NB_CHARACTERISTICS 4
typedef struct characteristics {
	int m; // Number of different classes
	int ** array;	// Relations between class and the other characteristics
} Characteristics;


Field * createField(int m, int n);

Characteristics * initCharacteristics(int n);

Animal * createAnimal(int class, Characteristics * species);

int addAnimal(Animal * this_animal, Tile * that_place);

void deleteCharacteristics(Characteristics * my_charact);

void deleteAnimal(Animal * my_animal);

void deleteTile(Tile * my_tile);

void deleteField(Field * turf);

#endif


