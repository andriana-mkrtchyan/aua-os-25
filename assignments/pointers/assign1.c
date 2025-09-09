#include <stdio.h>

int main(){
	
	int var = 5; // int variable initialized with a value
	int* p = &var; // pointer variable that points to the integer
	
	printf("Address of var using the value: %p\n", &var);
	printf("Address of var using the pointer: %p\n", p);

	printf("Value of var: %d\n", var);
	*p = 6;
	printf("Value of var after changing it with the pointer: %d\n", var);
	
	return 0;
}
