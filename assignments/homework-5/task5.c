#include <stdio.h>
#include <stdlib.h>


int main(){

	printf("Enter the number of students: ");
	int n;
	scanf("%d", &n);

	int *arr = malloc(n * sizeof(int)); // allocating memory for an array of size n
	if(!arr){
		perror("Fail malloc.");
		exit(EXIT_FAILURE);
	}

	
	printf("Enter the grades: ");
	scanf("%d", &arr[0]);// scanning the first grade separately, to initialize highest and lowest
			     // variables with it and compare others against them
	int highest = arr[0]; 
	int lowest = arr[0];

	for(int i = 1; i < n; i++){
		scanf("%d", &arr[i]); // getting the grade
		if(arr[i] > highest){
			highest = arr[i]; // updating the highest and lowest grades, if new one is found on the way
		}
		else if(arr[i] < lowest){
			lowest = arr[i];
		}
	}

	printf("Highest grade: %d\n", highest);
	printf("Lowest grade: %d\n", lowest);


	free(arr); // freeing the memory and safely ending the program
	arr = NULL;

	return 0;
}
