#include <stdio.h>

int main(){

	int n;
	char c;
	double d;
	short ns;

	printf("Size of int: %zu bytes, address: %p\n", sizeof(n), (void*)&n);
	printf("Size of char: %zu bytes, address: %p\n", sizeof(c), (void*)&c);
	printf("Size of double: %zu bytes, address: %p\n", sizeof(d), (void*)&d);
	printf("Size of short: %zu bytes, address: %p\n", sizeof(ns), (void*)&ns);
	
	return 0;
}
