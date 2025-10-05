#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, sum = 0;
	printf("Enter the number of elements: ");
	scanf("%d",&n);

	int *arr = (int *) malloc(n * sizeof(int));
	if(arr == NULL){
		perror("Malloc error.\n");
	}

	printf("Enter %d integers: ", n);
	for(int i = 0; i < n; i++){
		scanf("%d",(arr + i));
		sum += *(arr + i);
	}

	printf("Sum of the array: %d\n", sum);

	free(arr);
	arr = NULL;
	return 0;
}
