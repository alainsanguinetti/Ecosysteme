#include "./disp/disp.h"

int main()
{
	Field * Test = createField(2,2);
	int is_ok = 1;
	
	Characteristics * test = initCharacteristics(2);
	
	printf("%d\n", test->array[0][0]);
	
	// Creates an animal
	Animal * anitest = createAnimal(130,test);
	printf("%d\n", anitest->class);
	
	// Puts this animal at tile (0,1)
	is_ok = addAnimal(anitest, Test->array[0][1]);
	
	text_disp_field(Test);
	
	if(is_ok == 0){
		// Display its value
		printf("%d\n", Test->array[0][1]->animals->class);
	}
	
	deleteCharacteristics(test);
	
	deleteField(Test);

	return 0;
}

