#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFSIZE 512

int main(){

	char f1_path[64];
	char f2_path[64];

	printf("Path to the first file: ");
	scanf("%63s", f1_path);
	
	printf("Path to the second file: ");
	scanf("%63s", f2_path);

	int f1 = open(f1_path, O_RDONLY);
	if(f1 == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}	
	int f2 = open(f2_path, O_RDONLY);
	if(f2 == -1){
		perror("Fail open");
		close(f1);
		exit(EXIT_FAILURE);
	}

	char buf1[BUFSIZE]; // buffer to read the contents of the first file
	char buf2[BUFSIZE]; // buffer to read the contents of the second file
	ssize_t r1, r2; // number of bytes read from the first and second files, respectively
	off_t index = 0; // index to keep track of compared bytes

	while(1){
		r1 = read(f1, buf1, BUFSIZE); // reading into buffers
		r2 = read(f2, buf2, BUFSIZE);

		if(r1 < 0 || r2 < 0){
			perror("Read error");
			close(f1);
			close(f2);
			exit(EXIT_FAILURE);
		}

		ssize_t min = (r1 < r2) ? r1 : r2; // find the minimum of read bytes
		for(ssize_t i = 0; i < min; i++){
			if(buf1[i] != buf2[i]){
				printf("Files differ at byte %ld\n", index + i );
				close(f1);
				close(f2);
				exit(1);
			}
		} 

		if(r1 == 0 && r2 == 0){
			printf("Files are identical\n");
			break;
		}

		if(r1 != r2){
			printf("Files differ at byte %ld\n", index + min);
		}

		index += min;
	}


	close(f1);
	close(f2);

	



	return 0;
}
