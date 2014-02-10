#ifndef STRUCT
#define STRUCT

typedef struct animal {
	int rank;
	int moves_radius:1;
	int eat:1;
	int dies_after:5;
} Animal;

typedef struct tile {
	int qty_grass;
	Animal * preys;
	Animal * predators;
} Tile;

typedef struct terrain {
	Tile ** cases;
	int n;
	int m;
} Terrain;


#endif
