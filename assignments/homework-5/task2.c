#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, sum = 0;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	int *arr = (int*) calloc(n, sizeof(int));
	if(arr == NULL){
		perror("Calloc error.\n");
	}
	printf("Array after calloc: ");
	for(int i = 0; i < n; i++){
		printf("%d ", *(arr + i));
	}

	printf("\nEnter %d integers: ", n);
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
