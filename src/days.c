#include "days.h"

// Function that set up, run, and close a simulation
void simulation (SDL_Surface * screen) {
	Field * turf = NULL;
	
	// Set up the simulation
	printf("\n1 Setting up the simulation\n");
	turf = simulationSetUp();
	
	// Run the simulation
	printf("\n2 Running the simulation\n");
	days_simulation ( turf, screen );
	
	// Close the simulation
	printf ( "\n3 Closing the simulation\n" );
	deleteField(turf);
}

// Set up a simulation environment
Field * simulationSetUp () {
	int n = 1; 	// size of the field
	int days = 0;
	// int disp_mode = 0;
	
	// Characteristics
	Characteristics * species = initCharacteristics(2);
	
	// Field + animals
	printf("Field is a square of size n x n, please enter n : ");
	scanf("%d", &n);
	Field * turfSetUp = createField ( n, n );
	advancedFieldInitialization( turfSetUp, species );
	
	// Days
	printf("Enter the number of days : ");
	scanf("%d", &days);
	turfSetUp->nb_days_to_simulate = days;
	
	/*
	// Graphics
	printf ( "Do you want graphic display ?\n0: no\t1: yes\nYou choose : " );
	scanf("%d", &disp_mode);
	if (
	*/
	
	return turfSetUp;
}


// Full featured field initialization
void advancedFieldInitialization ( Field * turf, Characteristics * species ) {
	int nb_animats;
	int i, j;

	// Asks for the number of each animal to put
	printf("Please enter the number of animats wanted : ");
	scanf("%d", &nb_animats);
	
	// Put the preys and predators at opposite corners 
	for (i=0;i<(turf->n)/3;i++){
		for(j=((turf->m) * 2/3);j<turf->m;j++){
			if(nb_animats > 0) {
				addAnimal(createAnimal(1, species), turf->array[i][j]);
				addAnimal(createAnimal(2, species), turf->array[j][i]);
				nb_animats--;
			} else {
				break;
			}
		}
	}
	
	// Add the species table to the field
	turf->species = species;
}


// Put preys and predators in opposite corners (can be modified if necessary)
void initial_state (Field *turf, Characteristics * species){
	printf("Setting initial state\n");
	
	turf->species = species;
	
	int i;
	int j;
	for (i=0;i<(turf->n)/3;i++){
		for(j=((turf->m) * 2/3);j<turf->m;j++){
			addAnimal(createAnimal(1, species), turf->array[i][j]);
			addAnimal(createAnimal(2, species), turf->array[i][j]);
	
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
				
				moveAnimal(turf->array[i][j]->animals->specie, i, j, i+r, j+r2, turf);
			}
		}
	}
	
	// printf("Done moving all animals\n");
}

void day_simulation ( Field * turf ) {
	The_Grass_Is_Greener_When_You_Water_It ( turf );
	
	Sexy_Time ( turf );
	
	Eat_Dat_Motherfudger ( turf );
	
	Shave_Dat_Grass ( turf );
	
	Move_Bitch_GetOut_The_Way ( turf );
	
	Time_Is_A_Bitch ( turf );
	
	printStatistics ( turf );
}

void days_simulation ( Field * turf, SDL_Surface * screen ) {
	int i;
	for ( i = turf->nb_days_to_simulate ; i > 0 ; i-- ) {
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
							&& turf->array[i][j]->animals->specie > turf->array[i+a][j+b]->animals->specie){
								
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
			if(turf->array[i][j]->animals != NULL && turf->array[i][j]->animals->specie == 1 && turf->array[i][j]->qty_grass > 1){
				turf->array[i][j]->qty_grass--;
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
				
				// If the animal is young enough, he grows old
				if ( turf->array[i][j]->animals->age < 9 ) {
					turf->array[i][j]->animals->age++;
					
				// Else he dies
				} else {
					printf("It's time to die\n");
					deleteAnimal ( removeAnimal(turf->array[i][j]->animals->specie, turf->array[i][j]) );
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
			
			// If there is an animal that is old enough to have babies
			if (turf->array[i][j]->animals != NULL 
				&& turf->array[i][j]->animals->age > PUBERTY ){
					
				// Look for mates
				a = -1;
				
				while(a<2){
					b = -1;
					while(b<2 && a != 0 && (i+a)>=0 && (i+a)<turf->m){
						if ((j+b)>=0 && (j+b)<turf->m 
								&& b != 0
								&& turf->array[i+a][j+b]->animals != NULL 
								&& turf->array[i][j]->animals->specie == turf->array[i+a][j+b]->animals->specie){
									
							printf("Youhou !!\n");
							baby = createAnimal ( turf->array[i][j]->animals->specie , turf->species );
							
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
