#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void  *print(void *arg){
	printf("Thread %ld is running.\n", pthread_self());
	pthread_exit(NULL);
}

int main(){

	pthread_t t1, t2, t3; // to store threead id-s
	int ret1, ret2, ret3; // to store creation return values

	printf("Main running...\n");
	printf("Creating 3 threads...\n");

	ret1 = pthread_create(&t1, NULL, print, NULL);	
	ret2 = pthread_create(&t2, NULL, print, NULL);
	ret3 = pthread_create(&t3, NULL, print, NULL);
	
	if(ret1 || ret2 || ret3){
		perror("Fail pthread create.");
		exit(EXIT_FAILURE);
	} 


	ret1 = pthread_join(t1, NULL);
	ret2 = pthread_join(t2, NULL); 
	ret3 = pthread_join(t3, NULL);

	if(ret1 || ret2 || ret3){
		perror("Fail pthread join.");
		exit(EXIT_FAILURE);
	}



	printf("Main exiting...\n");

	return 0;
}
