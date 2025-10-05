#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, sum = 0;
	printf("Enter the number of elements: ");
	scanf("%d",&n); // scanning from user into n

	int *arr = (int *) malloc(n * sizeof(int)); // allocating memory for int array
	if(arr == NULL){
		perror("Malloc error.\n");
	}

	printf("Enter %d integers: ", n);
	// looping to read integers from user input, calculating the sum simultaneously
	for(int i = 0; i < n; i++){
		scanf("%d",(arr + i));
		sum += *(arr + i);
	}

	printf("Sum of the array: %d\n", sum);

	free(arr); // returning the allocated memory back to the system
	arr = NULL; // preventing further accidental access and using invalid pointer

	return 0;
}
