#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* my_realloc(void *ptr, size_t size);
int main(){

	printf("Enter 3 integers: ");
	int *arr = calloc(3, sizeof(int));
	for(int i = 0; i < 3; i++){
		scanf("%d", (arr + i));
	}
	int *temp = my_realloc(arr, 5 * sizeof(int));
	if(!temp){
		perror("Failed custom realloc");
		exit(EXIT_FAILURE);
	}
	arr = temp;
	printf("Enter 2 more integers: ");
	for(int i = 3; i < 5; i++){
		scanf("%d", (arr + i));
	}

	printf("Final array: ");
	for(int i = 0; i < 5; i++){
		printf("%d ", *(arr + i));
	}
	printf("\n");
	
	free(arr);
	arr = NULL;

	return 0;
}

void* my_realloc(void *ptr, size_t size){

	// checking if the ptr is null, realloc should behave like malloc
	if(ptr == NULL) return malloc(size);
	
	if(size == 0){ // and if size is 0, the memory should just be freed
		free(ptr);
		return NULL;
	}

	void* temp = malloc(size); // allocating the necessary memory with a new pointer
	memcpy(temp, ptr, size); // copying the containing data to destination temp from source ptr
	
		
	free(ptr); 
	ptr = NULL;

	return temp;
}
