#include <stdio.h>


struct Struct1{
	char a;
	int b;
	double c;
};

struct Struct2{
	double a;
	int b;
	char c;
};

struct Struct3{
	int a;
	double b;
	char c;
};

int main(){
	struct Struct1 s1;
	struct Struct2 s2;
	struct Struct3 s3;

	printf("Original struct size: %zu bytes\n", sizeof(s1));
	printf("Address of char: %p\n", (void*)&(s1.a));
	printf("Address of int: %p\n", (void*)&(s1.b));
	printf("Address of double: %p\n\n", (void*)&(s1.c));
	
	
	printf("Reordered struct size: %zu bytes\n", sizeof(s2));
        printf("Address of double: %p\n", (void*)&(s2.a));
        printf("Address of int: %p\n", (void*)&(s2.b));
        printf("Address of char: %p\n\n", (void*)&(s2.c));
	
        printf("Reordered struct size: %zu bytes\n", sizeof(s3));
        printf("Address of int: %p\n", (void*)&(s3.a));
        printf("Address of double: %p\n", (void*)&(s3.b));
        printf("Address of char: %p\n", (void*)&(s3.c));

	return 0;


}
