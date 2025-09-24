#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void func1(); // declaring two functions, described below
void func2();

time_t start, end;

int main(){
	time(&start); // time will be stored at start address
	printf("Printing some message and sleeping ... \n");
	sleep(5);
	atexit(func1); // pushed to stack
	atexit(func2); // pushed to stack

	return 0;
}

void func1(){
	printf("Func1: Program started execution at: %s\n", ctime(&start)); // just printing the start time, recorded in main
}

void func2(){
	time(&end); //storing end time
	printf("Func2: Program ended execution at: %s\n", ctime(&end)); 
	printf("Func2: Execution time: %.2f.\n", difftime(end, start));
}
