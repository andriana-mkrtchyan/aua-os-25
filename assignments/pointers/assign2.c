#include <stdio.h>

int main(){

	int arr[5] = {1, 2, 3, 4, 5};
	printf("Initial array:\n");
	for(int i = 0; i < 5; i++){
		printf("%d ", *(arr + i));	
	}
	printf("\n");

	printf("\nChanging array values ...\n");
	printf("\nModified array printed with the pointer:\n");
	for(int i = 0; i < 5; i++){
		printf("%d ", ++*(arr+i)); //incrementing each array value and printing at once
	}
	printf("\n");

	printf("\nModified array printed with the array name:\n");
	for(int i = 0; i < 5; i++){
		printf("%d ", arr[i]); // printing array values using the array name
	}
	printf("\n");


	return 0;
}
