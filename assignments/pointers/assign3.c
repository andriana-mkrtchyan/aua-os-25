#include <stdio.h>

void swap(int *a, int *b); // declaration of a function, defined below

int main(){
	
	int a = 5;
	int b = 6;

	printf("Before swap: a = %d, b = %d\n", a, b);
	swap(&a, &b); // swapping the values passing addresses as pointers
	printf("After swap: a = %d, b = %d\n", a, b);
	
	return 0;

}

// function that swaps two integer values using pointes
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}



