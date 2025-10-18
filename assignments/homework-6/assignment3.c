#include <stdio.h>

struct Struct1{
	char a;
	int b;
	double c;
};

#pragma pack(1)
struct Struct2{
	char a;
	int b;
	double c;
};

#pragma pack(2)
struct Struct3{
        int a;
        double b;
        char c;
};

#pragma pack(4)
struct Struct4{
        char a;
        double b;
        int c;
};

int main(){

	struct Struct1 s1;
	struct Struct2 s2;
        struct Struct3 s3;
        struct Struct4 s4;

	printf("Size of struct: %zu\n", sizeof(s1));
	printf("Address of char: %p\n", (void*)&s1.a);
        printf("Address of int: %p\n", (void*)&s1.b);
        printf("Address of double: %p\n\n", (void*)&s1.c);
	
	printf("Size of struct: %zu\n", sizeof(s2));
        printf("Address of char: %p\n", (void*)&s2.a);
        printf("Address of int: %p\n", (void*)&s2.b);
        printf("Address of double: %p\n\n", (void*)&s2.c);
	
        printf("Size of struct: %zu\n", sizeof(s3));
        printf("Address of int: %p\n", (void*)&s3.a);
        printf("Address of double: %p\n", (void*)&s3.b);
        printf("Address of char: %p\n\n", (void*)&s3.c);

        printf("Size of struct: %zu\n", sizeof(s4));
        printf("Address of char: %p\n", (void*)&s4.a);
        printf("Address of double: %p\n", (void*)&s4.b);
        printf("Address of int: %p\n", (void*)&s4.c);

	return 0;
}
