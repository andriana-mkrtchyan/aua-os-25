#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct pthreadArgs{
	int num;
};

void* square(void* arg){
	struct pthreadArgs *args = (struct pthreadArgs*)arg;
	int num = args -> num;
	printf("Square of %d is %d.\n", num, num*num);
	free(args);
	pthread_exit(NULL);
}

int main(){

	int arr[] = {1, 2, 3, 4, 5};
	pthread_t t[5]; // container fot pthreads

	// printing the array
	printf("Main executing...\n");
	printf("Array: ");
	for(int i = 0; i < 5; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");


	// creating the threads
	for(int i = 0; i < 5; i++){
		struct pthreadArgs *arg = malloc(sizeof(struct pthreadArgs));
		arg->num = arr[i];
		int ret = pthread_create(&t[i], NULL, square, arg );
		if(ret){
			perror("Fail create thread");
			exit(EXIT_FAILURE);
		}
	}

	// waiting for every thread to end execution
	for(int i = 0; i < 5; i++){
		int ret = pthread_join(t[i], NULL);
		if(ret){
			perror("Fail create thread");
			exit(EXIT_FAILURE);
		}	
	}

	return 0;
}
