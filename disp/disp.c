#include "./disp.h"

void graphic_ecosysteme(Field * turf){}

void text_disp_field(Field * turf){
	int i = 0;
	int j = 0;
	
	printf("This field is of size : %d x %d\n", turf->m, turf->n);
	
	for(i = 0; i < turf->m; i++){
		for(j = 0; j < turf->n; j++){
			text_disp_pos(turf, i, j);
		}
	}
}

void text_disp_pos(Field * turf, int x, int y){
	printf("Displaying tile at position x = %d, y = %d", x, y);
	text_disp_tile(turf->array[x][y]);
}

void text_disp_tile(Tile * cell){
	printf("\tGrass : %d \t", cell->qty_grass);
	if(cell->animals == NULL){
		printf("No animals on this tile\n");
	}else{
		printf("Specie : %d\n", cell->animals->class);
	}
}
