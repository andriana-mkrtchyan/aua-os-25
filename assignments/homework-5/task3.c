#include <stdio.h>
#include <stdlib.h>

int main(){

	int *arr = malloc(10 * sizeof(int));
	if(!arr){
		perror("Fail malloc.\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter 10 elements: ");
	for(int i = 0; i < 10; i++){
		scanf("%d", (arr + i));
	}

	int *temp = realloc(arr, 5 * sizeof(int));
	if(!temp){
		perror("Fail realloc.\n");
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
