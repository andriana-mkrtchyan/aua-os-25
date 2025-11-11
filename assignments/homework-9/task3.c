#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *print_numbers(void* arg){
	for(int i = 1; i < 6; i++){
		printf("%d ", i);
	}
}


int main(){
	
	pthread_t threads[3]; // array of pthreads
	for(int i = 0; i < 3; i++){ // create 3 threads and handle failure
		int ret = pthread_create(&threads[i], NULL, print_numbers, NULL);
		if(ret){
			perror("Fail create thread");
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < 3; i++){
		int ret = pthread_join(threads[i], NULL);
		if(ret){
			perror("Fail join thread");
			exit(EXIT_FAILURE);
		}
	}
	
	printf("\n");

	return 0;
}
