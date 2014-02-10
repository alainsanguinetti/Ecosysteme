#ifndef STRUCT
#define STRUCT

typedef struct animal Animal;
struct animal {
	int rank;
	int moves_radius;
	int eat;
	int dies_after;
	Animal * next_animal;
};

typedef struct tile {
	int qty_grass;
	Animal * animals;
} Tile;

typedef struct terrain {
	Tile ** cases;
	int n;
	int m;
} Terrain;


#endif
