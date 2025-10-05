#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, sum = 0;
	printf("Enter the number of elements: ");
	scanf("%d", &n); 
	int *arr = calloc(n, sizeof(int)); // allocating array size of n
	if(arr == NULL){
		perror("Calloc error.\n");
		exit(EXIT_FAILURE);
	}

	printf("Array after calloc: ");
	// printing the initally empty array, with all elems = 0, as calloc initializes int array elements with 0
	for(int i = 0; i < n; i++){
		printf("%d ", *(arr + i));
	}

	printf("\nEnter %d integers: ", n);
	// looping to read elements into arr and calculating the sum at once
	for(int i = 0; i < n; i++){
		scanf("%d", (arr + i));
		sum += *(arr + i);
	}

	double avg = (double) sum/n;

	printf("Updated array: ");
        for(int i = 0; i < n; i++){
                printf("%d ", *(arr + i));
        }

	printf("\nAverage of the array: %.2f\n", avg);

	free(arr);
	arr = NULL;
	return 0;

}
