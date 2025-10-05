#include <stdio.h>
#include <stdlib.h>

int main(){

	int *arr = malloc(10 * sizeof(int));
	
	// handling allocation error
	if(!arr){
		perror("Fail malloc.\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter 10 elements: ");
	for(int i = 0; i < 10; i++){
		scanf("%d", (arr + i)); // initializing the array with user input
	}

	int *temp = realloc(arr, 5 * sizeof(int)); // using temp pointer to reallocate the memory, 
						   // so that in case of allocation error the
						   // data and pointer remain protected
	if(!temp){
		perror("Fail realloc.\n");
		free(arr);
		arr = NULL;
		exit(EXIT_FAILURE);
	}

	arr = temp;
	printf("Array after resizing: ");
	for(int i = 0; i < 5; i++){
                printf("%d ", *(arr + i));
        }
	printf("\n");

	free(arr);
	arr = NULL;

	return 0;
}
