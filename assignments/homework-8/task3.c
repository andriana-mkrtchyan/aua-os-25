#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(){

	char path[50];
	printf("Enter a path to a file: ");
	scanf("%49s", path);

	int fd = open(path, O_RDONLY);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}
	off_t size = lseek(fd, 0, SEEK_END); // to indicate the size of the file
	if(size == (off_t)-1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}
	
	if(size == 0){
		write(1, "\n", 1);
		close(fd);
		return 0;
	}

	//printf("File size: %ld\n", size);

	char b; // to read a byte into
	for(off_t pos = size - 1; pos >=0; pos--){ // moving position from the end of the file to the beginning
		if(lseek(fd, pos, SEEK_SET) == (off_t)-1) {
			perror("Fail seek");
			close(fd);
			exit(EXIT_FAILURE);
		}

		ssize_t b_read = read(fd, &b, sizeof(char)); // keeps number of bytes effectively read
		if(b_read < 0){
			perror("Fail read");
			close(fd);
			exit(EXIT_FAILURE);
		}

		if(write(1, &b, sizeof(char)) != 1){ // if other than 1 byte was written
			perror("Fail write");
			close(fd);
			exit(EXIT_FAILURE);
		}

		if(pos == 0){
			break;
		}
	
	}

	printf("\n");

	if(close(fd) < 0){
		perror("Fail close");
		exit(EXIT_FAILURE);
	}


	
	
	return 0;
}
