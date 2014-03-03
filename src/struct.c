#include "struct.h"

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

Characteristics * initCharacteristics(int n){
	Characteristics * new = NULL;
	int i,j;
	
	// Allocate n rows
	new = (Characteristics *)malloc(sizeof(Characteristics));
	new->array = (int **)malloc(10 * n * sizeof(int));
	
	// For each specie creates corresponding characteristics
	for(i = 0; i < n; i++){
		
		// For each specie, creates 10 stages of life : from 0 to 9
		for(j = 0; j < 10; j++){
			new->array[i * 10 + j] = (int *)malloc(NB_CHARACTERISTICS * sizeof(int));
		
			new->array[i * 10 + j][0] = 100 * (i + 1) + 10 * j; 	// ex : 120
			
			
			new->array[i * 10 + j][1] = 1;	// moves radius
			new->array[i * 10 + j][2] = 1;	// eat
			new->array[i * 10 + j][3] = 5;	// dies after
		}
	}
	
	new->m = 10 * n;
	
	return new;
}

Animal * createAnimal(int class, Characteristics * species){
	Animal * new_animal = NULL;
	new_animal = (Animal *)malloc(sizeof(Animal));
	int i = 0;
	while (species->array[i][0] != class && i < species->m){
		i++;
	}
	// printf("wow : %d\n",species->array[i][0]);
	new_animal->class = species->array[i][0];
	
	new_animal->moves_radius = species->array[i][1];
	new_animal->eat = species->array[i][2];
	new_animal->dies_after = species->array[i][3];
	return new_animal;
}

int addAnimal(Animal * this_animal, Tile * that_place){
	
	// Check if tile is not occupied by animals of an other specie
	if(that_place->animals == NULL || that_place->animals->class == this_animal->class){

		// if not, tile points to us and we point to what was there
		this_animal->next_animal = that_place->animals;
		that_place->animals = this_animal;

		return 0;
	}else{
	// else
		return 1;
	}
}

Animal * removeAnimal(int class, Tile * that_place){
	Animal * this_animal = NULL;
	Animal * temp_animal = NULL;
	
	// Check if animal is present
	if(that_place->animals->class == class){
		// if yes, select the first animal
		this_animal = that_place->animals;
		
		// then remove it from the tile
		temp_animal = this_animal->next_animal;
		that_place->animals = temp_animal;
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
	
	// Get the adresses of start tile and end tile
	// Check if they belong to the field
	if(x < turf->m && y < turf->n && next_x < turf->m && next_y < turf->n){
		// if yes, remember the references
		start = turf->array[x][y];
		end = turf->array[next_x][next_y];
	
		// Then remove animal
		this_animal = removeAnimal(class, start);
		
		// if animal is removed
		if(this_animal != NULL){
			// add animal to the next place
			result = addAnimal(this_animal, end);
		}
	}
	
	return result;
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
		deleteAnimal(my_animal->next_animal);
		free(my_animal);
	}
}


