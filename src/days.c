#include "days.h"


// Put preys and predators in opposite corners (can be modified if necessary)
void initial_state (Field *turf, Characteristics * species){
int i;
int j;
	for (i=0;i<(turf->n)/3;i++){
		for(j=((turf->n) * 2/3);j<turf->n;j++){
			addAnimal(createAnimal(100, species), turf->array[i][j]);
			addAnimal(createAnimal(200, species), turf->array[j][i]);	
		}
	}	
}


void Move_Bitch_GetOut_The_Way(Field *turf){
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
void day_simulation(Field *turf){
	Move_Bitch_GetOut_The_Way(turf);
	The_Grass_Is_Greener_When_You_Water_It(turf);
	Eat_Dat_Motherfudger(turf);
	Shave_Dat_Grass(turf);
	Time_Is_A_Bitch(turf);
	Sexy_Time(turf);
}

void days_simulation(int nb_days, Field * turf){
	int i;
	for(i=0;i<nb_days;i++){
		day_simulation(turf);
	}
}

void The_Grass_Is_Greener_When_You_Water_It(Field *turf){
int i;
int j;
for (i=0;i<turf->n;i++){
	for(j=0;j<turf->m;j++){
		turf->array[i][j]->qty_grass = turf->array[i][j]->qty_grass + 1;
	}
}
}

void Eat_Dat_Motherfudger(Field *turf){
	int i;
	int j;
	int a = -1;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			while(a<2 && turf->array[i][j]->animals != NULL){
				int b = -1;
				while(b<2 && turf->array[i][j]->animals != NULL){
					if (turf->array[i][j]->animals->class/100 < turf->array[i+a][j+b]->animals->class/100){
						deleteAnimal(turf->array[i+a][j+b]->animals);
						moveAnimal(turf->array[i][j]->animals->class,i,j,i+a,j+b,turf);
						
					}
					b = b + 1;
				}
				a = a + 1;
			}
		}
	}
}

void Shave_Dat_Grass(Field *turf){
	int i;
	int j;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			if(turf->array[i][j]->animals->class/100 == 1 && turf->array[i][j]->qty_grass > 1){
				turf->array[i][j]->qty_grass = turf->array[i][j]->qty_grass - 1;
			}
		}
	}
}

void Time_Is_A_Bitch(Field *turf){
	int i;
	int j;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			if(turf->array[i][j]->animals->class/10 <9){
				turf->array[i][j]->animals->class = turf->array[i][j]->animals->class + 10;
			}
			else{
				deleteAnimal(turf->array[i][j]->animals);
				turf->array[i][j]->animals = NULL;
			}
		}
	}
}

void Sexy_Time(Field *turf){
	int i;
	int j;
	int a = -1;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			while(a<2){
				int b = -1;
				while(b<2){
					if (turf->array[i][j]->animals->class/100 == turf->array[i+a][j+b]->animals->class/100){
						createAnimal((turf->array[i][j]->animals->class/100)*100 , turf->species);
					}
					b = b + 1;
				}
				a = a + 1;
			}
		}
	}
}








		
