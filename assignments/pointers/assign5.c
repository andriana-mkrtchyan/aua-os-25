#include <stdio.h>

int main(){


	char str[] = "Hello";
	char *p = str;
	//printf("%p\n", p);
	//printf("%p\n", &str[0]);
	
	int strsize = sizeof(str)/sizeof(str[0]);
	printf("Printing the string, character by character:\n");
	for(int i = 0; i < strsize; i++){
		printf("%c", *(str + i));
	}
	printf("\n");

	// getting the size of the string using pointer arithmetics
	while(*p != '\0'){ // the '\0' in c indicates the end of a string
		p++;
	}
	int len = p - str; // the length can be calculated as the difference between the last and first char addresses in the string,
			   // as string is stored in consecutive memory locations
	printf("String length: %d\n", len);
	return 0;
}
