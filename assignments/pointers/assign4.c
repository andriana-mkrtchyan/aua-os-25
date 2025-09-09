#include <stdio.h>

int main(){

	int var = 5;
	int *p = &var;
	int **dp = &p;

	printf("Variable: %d\n", var);
	printf("Using pointer: %d\n", *p);
	printf("Using double pointer: %d\n", *(*dp));
	return 0;
}
