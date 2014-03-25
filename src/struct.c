#include "struct.h"

// ### ### ### ### ### Main program utilities

// Empty function to display nothing
int quietprint ( __const char *__restrict __format, ... ){
	return EXIT_SUCCESS;
}

// Read the arguments passed to the program. Returns true if none or if correct arguments.
bool readArguments ( int argc, char * argv[] ) {
	// No arguments case
	if (argc == 1) {
		// So let's be quiet !
		verbosemode = QUIET;
		return true;
	}
	// If there is a second argument asking to be verbose
	else if (strcmp(argv[1], "-v") == 0) { /* Process optional arguments. */
		// Entering verbose mode
		verbosemode = VERBOSE;
		
		// So let's be verbose !
		myPrintf[verbosemode]("Entering verbose mode\n");
		
		// Execution of the program may continue
		return true;
	}
	// If it does not matches the previous cases, then this is an error.
	else {
		// Display usage statement
		fprintf(stderr, "\nusage:\tfilename [-v]\n\t-v asks for verbose mode\n\n");
		
		// And stop execution of program
		return false;
		// exit(EXIT_FAILURE);
	}
}

// ### ### ### ### ### Field and animals utilities

Field * createField(int m, int n){
	Field * turf = NULL;
	int i, j;
	
	
	turf = (Field *)malloc(sizeof(Field));
	
	turf->array = (Tile ***)malloc(m * sizeof(Tile **));
	
	for(i = 0; i < m; i++){
		turf->array[i] = (Tile **)malloc(n * sizeof(Tile *));
		
		if(turf->array[i] != NULL){
			for(j = 0; j < n; j++){
				turf->array[i][j] = (Tile *)malloc(sizeof(Tile));
				turf->array[i][j]->qty_grass = 0;
				turf->array[i][j]->animals = NULL;
			}
		}
	}
	
	turf->m = m;
	turf->n = n;
	
	return turf;
}

Characteristics * initCharacteristics ( int n ) {
	Characteristics * new = NULL;
	int i;
	
	// Allocate n rows
	new = ( Characteristics * ) malloc ( sizeof(Characteristics) );
	new->array = ( int ** ) malloc ( n * sizeof(int) );
	
	// For each specie creates corresponding characteristics
	for(i = 0; i < n; i++){
		new->array[i] = ( int * ) malloc ( NB_CHARACTERISTICS * sizeof(int) );

		new->array[i][0] = i+1;	// specie
		new->array[i][1] = 1;	// moves radius
		new->array[i][2] = 1;	// eat
		new->array[i][3] = 5;	// dies after
	}
	
	new->m = n;
	
	return new;
}

Animal * createAnimal ( int specie, Characteristics * species ) {
	// Just in case, check that the species table exists
	if ( species != NULL ) {
		
		// Allocates the new animal
		Animal * new_animal = NULL;
		new_animal = ( Animal * ) malloc ( sizeof(Animal) );
		int i = 0;

		// printf ( "wow : %d\n", species->array[i][0] );

		/* We look for the correct entry in the characteristics table */
		while ( i < species->m - 1 && species->array[i][0] != specie ) {
			i++;
		}

		// printf("wow, i = %d\n",i);
		
		/* Set corresponding characteristics */
		new_animal->specie = species->array[i][0];
		new_animal->moves_radius = species->array[i][1];
		new_animal->eat = species->array[i][2];
		new_animal->dies_after = species->array[i][3];
		new_animal->age = 0;
		
		
		return new_animal;

	} else {
		return NULL;
	}
}

int addAnimal(Animal * this_animal, Tile * that_place){
	
	// Check if tile is available
	if ( that_place->animals == NULL ) {

		// if not, tile points to us and we point to what was there
		that_place->animals = this_animal;

		return 1;
	}else{
		return 0;
	}
}

Animal * removeAnimal(int specie, Tile * that_place){
	Animal * this_animal = NULL;
	
	// Check if animal is present
	if(that_place->animals->specie == specie){
		// if yes, select the first animal
		this_animal = that_place->animals;
		
		// then remove it from the tile
		that_place->animals = NULL;
	}
		
	// Return the adress of the selected animal		
	// If not, return NULL
	return this_animal;
}

int moveAnimal(int class, int x, int y, int next_x, int next_y, Field * turf){
	int result = 0;
	Tile * start = NULL;
	Tile * end = NULL;
	Animal * this_animal = NULL;

	//printf("Trying to move an animal of class %d, from tile %d, %d to tile %d, %d\n", class, x, y, next_x, next_y);

	// Get the adresses of start tile and end tile
	// Check if they belong to the field
	if(x < turf->m 
			&& y < turf->n 
			&& next_x < turf->m 
			&& next_y < turf->n 
			&& next_x >= 0 
			&& next_y >= 0){

		// if yes, remember the references
		start = turf->array[x][y];
		end = turf->array[next_x][next_y];

		// Then remove animal
		this_animal = removeAnimal(class, start);

		// if animal is removed
		if(this_animal != NULL){
			// add animal to the next place
			result = addAnimal(this_animal, end);

			if(result == 0){
				addAnimal(this_animal, start);
			}else{
				//printf("Moved an animal\n");
			}
		}
	}

	return result;
}

// Prints the number of each animats
void printStatistics ( Field * turf ) {
	int k = 0;			// Counter on species
	int i, j;			// Counter on array
	int nb_animats = 0;	// Counter on animats

	// For every kind of animats, we loop through the field and print the number we found
	while ( k < turf->species->m ) {
		for ( i = 0 ; i < turf->m ; i++ ) {
			for ( j = 0 ; j < turf->n ; j++ ) {

				// If there is animats of the specie we are currently counting, we increment the counter
				if ( turf->array[i][j]->animals != NULL 
						&& turf->array[i][j]->animals->specie == k + 1 ) {
					
					printf ( "Animats of class %d, k = %d\n", turf->array[i][j]->animals->specie, k + 1 );
					
					nb_animats++;
				}

			}
		}

		printf ( "There are %d animats of specie %d\n", nb_animats, (k + 1) );

		// Counter reset
		nb_animats = 0;

		// Move on to the next specie
		k++;
	}
}

void deleteCharacteristics(Characteristics * my_charact){
	int i;
	for(i = 0; i < my_charact->m; i++){
		free(my_charact->array[i]);
	}
	
	free(my_charact->array);
	
	free(my_charact);
}

void deleteField(Field * turf){
	int i, j;
	
	deleteCharacteristics(turf->species);
	
	for(i=0; i < turf->m; i++){
		for(j=0; j < turf->n; j++){
			deleteTile(turf->array[i][j]);
		}
		free(turf->array[i]);
	}free(turf->array);
	free(turf);
}

void deleteTile(Tile * my_tile){
	if(my_tile != NULL){
		deleteAnimal(my_tile->animals);
		free(my_tile);
	}
}

void deleteAnimal(Animal * my_animal){
	if(my_animal != NULL){
		printf("Deleting animal from specie %d\n", my_animal->specie);
		free(my_animal);
	}
}


