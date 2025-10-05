#include <stdio.h>
#include <stdlib.h>

int main(){

	char **arr = malloc(3 * sizeof(char*));
	if(!arr){
		perror("Fail malloc.");
		exit(EXIT_FAILURE);
	};

	for(int i = 0; i < 3; i++){
		*(arr + i) = malloc(50 * sizeof(char));
		if(!*(arr + i)){
			perror("Fail malloc");
			exit(EXIT_FAILURE);
		}
	}

	printf("Enter 3 strings: ");
	for(int i = 0; i < 3; i++){
		scanf("%49s", *(arr + i));
	}
	printf("You entered: ");
	for(int i = 0; i < 3; i++){
		printf("%s ", *(arr + i));
	}

	char **temp = realloc(arr,5  * sizeof(char*));
	if(!temp){
		perror("Fail realloc.");
		exit(EXIT_FAILURE);
	}
	
	arr = temp;

	for(int i = 0; i < 2; i++){
		*(arr + i + 3) = malloc(50 * sizeof(char));
		if(!*(arr + i + 3)){
			perror("Fail malloc.");
			exit(EXIT_FAILURE);		
		}
	}


	printf("\nEnter 2 more strings: ");
        for(int i = 0; i < 2; i++){
                scanf("%49s", *(arr + i + 3));
        }	
	
	printf("All strings: ");
        for(int i = 0; i < 5; i++){
                printf("%s ", *(arr + i));
        }
	printf("\n");

	for(int i = 0; i < 5; i++){
		free(*(arr + i));
	}
	free(arr);
	arr = NULL;
	return 0;

}
