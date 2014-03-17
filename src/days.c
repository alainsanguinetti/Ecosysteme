#include "days.h"


// Put preys and predators in opposite corners (can be modified if necessary)
void initial_state (Field *turf, Characteristics * species){
	printf("Setting initial state\n");
	
	turf->species = species;
	
	int i;
	int j;
	for (i=0;i<(turf->n)/3;i++){
		for(j=((turf->m) * 2/3);j<turf->m;j++){
			addAnimal(createAnimal(100, species), turf->array[i][j]);
			addAnimal(createAnimal(200, species), turf->array[j][i]);	
		}
	}	
}


void Move_Bitch_GetOut_The_Way(Field *turf){
	printf("Moving all animals\n");
	
	int i;
	int j;
	srand(time(NULL));
	int r, r2;
	for (i=0;i<turf->m;i++){
		for(j=0;j<turf->n;j++){
			
			if (turf->array[i][j]->animals != NULL){
				do{
					r = rand()%3 - 1;
					r2 = rand()%3 - 1;
					// printf("r = %d, r2 = %d\n", r, r2);
				}while(r == 0 && r2 == 0);
				
				// printf("i = %d, j = %d, i+r = %d, j+r2 = %d\n", i, j, i+r, j+r2);
				
				moveAnimal(turf->array[i][j]->animals->class, i, j, i+r, j+r2, turf);
			}
		}
	}
	
	// printf("Done moving all animals\n");
}

void day_simulation(Field *turf){
	The_Grass_Is_Greener_When_You_Water_It(turf);
	Sexy_Time(turf);
	Eat_Dat_Motherfudger(turf);
	Shave_Dat_Grass(turf);
	Move_Bitch_GetOut_The_Way(turf);
	Time_Is_A_Bitch(turf);
}

void days_simulation(int nb_days, Field * turf, SDL_Surface * screen){
	int i;
	for(i=0;i<nb_days;i++){
		day_simulation(turf);
		user_disp_field(turf, screen, SDL);
	}
}

void The_Grass_Is_Greener_When_You_Water_It(Field *turf){
	printf("Growing grass everywhere\n");
	
	int i;
	int j;
	
	for (i=0;i<turf->m;i++){
		for(j=0;j<turf->n;j++){
			turf->array[i][j]->qty_grass++;
		}
	}
}

void Eat_Dat_Motherfudger(Field *turf){
	printf("Eating animals\n");
	
	int i;
	int j;
	int a, b;
	for (i=0;i<turf->m;i++){
		for(j=0;j<turf->n;j++){
			a = -1;
			while(a<2 && turf->array[i][j]->animals != NULL){
				
				b = -1;
				
				while(b<2 && (i+a)>=0 && (i+a)<turf->m){
								
					if ((j+b)>=0 && (j+b)<turf->n 
							&& turf->array[i+a][j+b]->animals != NULL
							&& b != 0
							&& a != 0
							&& turf->array[i][j]->animals->class/100 > turf->array[i+a][j+b]->animals->class/100){
								
						deleteAnimal(turf->array[i+a][j+b]->animals);
						turf->array[i+a][j+b]->animals = NULL;
						
						// moveAnimal(turf->array[i][j]->animals->class,i,j,i+a,j+b,turf);
						printf("yummy!!!\n");
					}
					b++;
				}
				a++;
			}
		}
	}
	
	printf("Animals are done eating\n");
}

void Shave_Dat_Grass(Field *turf){
	printf("Eating the grass\n");
	
	int i;
	int j;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			if(turf->array[i][j]->animals != NULL && turf->array[i][j]->animals->class/100 == 1 && turf->array[i][j]->qty_grass > 1){
				turf->array[i][j]->qty_grass = turf->array[i][j]->qty_grass - 1;
			}
		}
	}
}

void Time_Is_A_Bitch(Field *turf){
	printf("Checking for animals too old\n");
	
	int i;
	int j;
	for (i=0;i<turf->n;i++){
		for(j=0;j<turf->m;j++){
			if(turf->array[i][j]->animals != NULL){
				//printf("Animal is aged %d\n", (turf->array[i][j]->animals->class/10)%10);
				if((turf->array[i][j]->animals->class/10)%10 < 9){
					turf->array[i][j]->animals->class = turf->array[i][j]->animals->class + 10;
				}
				else{
					printf("It's time to die\n");
					deleteAnimal(removeAnimal(turf->array[i][j]->animals->class, turf->array[i][j]));
					turf->array[i][j]->animals = NULL;
				}
			}
		}
	}
}

void Sexy_Time(Field *turf){
	printf("Sexy time\n");
	
	int i;
	int j;
	int a, b;
	int c, d;
	int baby_delivered;
	Animal * baby = NULL;

	for (i=0;i<turf->m;i++){
		for(j=0;j<turf->n;j++){
			if (turf->array[i][j]->animals != NULL && (turf->array[i][j]->animals->class%100)/10 > PUBERTY ){
				a = -1;
				while(a<2){
					b = -1;
					while(b<2 && a != 0 && (i+a)>=0 && (i+a)<turf->m){
						if ((j+b)>=0 && (j+b)<turf->m 
								&& b != 0
								&& turf->array[i+a][j+b]->animals != NULL 
								&& turf->array[i][j]->animals->class/100 == turf->array[i+a][j+b]->animals->class/100){
									
							printf("Youhou !!\n");
							baby = createAnimal((turf->array[i][j]->animals->class/100)*100 , turf->species);
							
							baby_delivered = 0;
							
							/* We look for available tile for our dear newborn */
							if(baby != NULL){
								c = -1;
								
								while(c<2 && baby_delivered == 0){
									d = -1;
									
									while(d<2 && c != 0 
											&& (i+c)>=0 
											&& (i+c)<turf->m
											&& j+d >= 0
											&& j+d < turf->n
											&& baby_delivered == 0){
												
										baby_delivered = addAnimal(baby, turf->array[i+c][j+d]);
										if(baby_delivered == 1){
											printf("Baby delivered\n");
										}
										
										d++;
									}
										
									c++;
								}
								
								if(baby_delivered == 0){
									deleteAnimal(baby);

								}
							}
						}
						b++;
					}
					a++;
				}
			}
		}
	}
}








		
