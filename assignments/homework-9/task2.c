#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// structure to be passed as parameter to thread startup function
struct ThreadArgs {
	int *arr; // pointer to the array
	int start; // start index of the array part
	int end;   // end index of the array part
};

// function to calculate partial sum of an array, from index start(included) to end(excluded)
int sum_arr(int* arr, int start, int end){
	int sum = 0;
	for(int i = start; i < end; i++){
		sum += *(arr + i);
	}
	return sum;
}

// param arg: pointer to struct ThreadArgs 
void *start_thread_sum(void *arg){
	struct ThreadArgs *args = (struct ThreadArgs *)arg;
       	int sum = sum_arr(args->arr, args->start, args->end);
	printf("Thread %ld working. Sum arr[%d;%d] = %d\n", pthread_self(),args->start, args->end, sum);
	pthread_exit(NULL);
}


int main(){

	int arr[] = {1, 1, 2, 2, 3, 3, 4, 4};
	ssize_t len = sizeof(arr) / sizeof(int); // size of the array

	pthread_t t1, t2;
	struct ThreadArgs args1 = {arr, 0, len/2}; // let thread1 calculate partial sum of the 1st half
	struct ThreadArgs args2 = {arr, len/2, len}; // and thread2 - the 2nd half of the array

	printf("Main executing...\n");
	printf("Array: ");
	for(int i = 0; i < len; i++){
		printf("%d ", arr[i]);
	}

	printf("\nCalling threads to calculate partial sums...\n");
	int ret1 = pthread_create(&t1, NULL, start_thread_sum, &args1); 
	if(ret1){
		perror("Fail create thread");
		exit(EXIT_FAILURE);
	}

	
	int ret2 = pthread_create(&t2, NULL, start_thread_sum, &args2);
	if(ret2){
		perror("Fail create thread");
		exit(EXIT_FAILURE);
	}

	
	ret1 = pthread_join(t1, NULL); // waiting for thread1 to end execution
	if(ret1){
		perror("Fail join thread");
		exit(EXIT_FAILURE);
	}

	
	ret2 = pthread_join(t2, NULL); // and for thread2
	if(ret2){
		perror("Fail join thread");
		exit(EXIT_FAILURE);
	}

	return 0;
}
