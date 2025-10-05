#include <stdio.h>
#include <stdlib.h>


int main(){

	printf("Enter the number of students: ");
	int n;
	scanf("%d", &n);

	int *arr = malloc(n * sizeof(int));
	if(!arr){
		perror("Fail malloc.");
		exit(EXIT_FAILURE);
	}

	
	printf("Enter the grades: ");
	scanf("%d", &arr[0]);
	int highest = arr[0];
	int lowest = arr[0];

	for(int i = 1; i < n; i++){
		scanf("%d", &arr[i]);
		if(arr[i] > highest){
			highest = arr[i];
		}
		else if(arr[i] < lowest){
			lowest = arr[i];
		}
	}

	printf("Highest grade: %d\n", highest);
	printf("Lowest grade: %d\n", lowest);

	free(arr);
	arr = NULL;

	return 0;
}
