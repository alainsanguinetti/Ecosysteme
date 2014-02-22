#include "struct.h"
#include "days.h"
#include <time.h>
#include <stdlib.h>






void initial_state (Field *turf, Characteristics * species){
int i;
int j;
	for (i=0;i<(turf->n)/3;i++){
		for(j=((turf->n) * 2/3);j<turf->n;j++){
			addAnimal(createAnimal(100, species), turf->array[i][j]);// Put preys and predators in opposite corners
			addAnimal(createAnimal(200, species), turf->array[j][i]);	
		}
	}	
}


void day_simulation(Field *turf){
	int i;
	int j;
	srand(time(NULL));
	int r = rand()%3 -1;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			if (turf->array[i][j]->animals != NULL){
			moveAnimal(turf->array[i][j]->animals->class, i, j, i+r, j+r, turf);
			}
		}
	}
}

void days_simulation(int nb_days, Field * turf){
	int i;
	for(i=0;i<nb_days;i++){
		day_simulation(turf);
	}
}















		
