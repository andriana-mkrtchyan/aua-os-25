#include <stdio.h>
#include <stdlib.h>

int main(){

	char **arr = malloc(3 * sizeof(char*)); // as strings are pointers to char array, a string array
						// should be a so-said pointer to pointers
	if(!arr){ // handling allocation error
		perror("Fail malloc.");
		exit(EXIT_FAILURE);
	};

	// allocating memory for each string in the array
	for(int i = 0; i < 3; i++){
		*(arr + i) = malloc(50 * sizeof(char));
		if(!*(arr + i)){
			perror("Fail malloc");
			exit(EXIT_FAILURE);
		}
	}

	printf("Enter 3 strings: ");
	for(int i = 0; i < 3; i++){
		scanf("%49s", *(arr + i)); // telling how many characters to read enhances memory management
					   // reading 49 chars leaves the last place for '\0', indicateing the
					   // end of string
	}
	printf("You entered: ");
	for(int i = 0; i < 3; i++){
		printf("%s ", *(arr + i));
	}

	char **temp = realloc(arr,5  * sizeof(char*)); // reallocating the array to caontain 5 strings in total
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

	free(arr); // freeing the array to safely end the program
	arr = NULL;
	
	return 0;


}
