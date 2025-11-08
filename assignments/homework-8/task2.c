#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(){

	int fd; // the file descriptor
       	fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // open the data.txt and clear the contents
								   // or create it
	if(fd == -1){ // open returns -1 in case of failure
		perror("Fail open");
		exit(EXIT_FAILURE);
	}

	char *ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	ssize_t nr; // to keep number of read/write bytes
start:
	nr = write(fd, ascii, 26); // try writing ascii to data.txt
	if(nr == -1){
		if(errno == EINTR){ // if errno is set to EINTR, this means a signal was received before any bytes
				    // could be read, and the call can be reissued
			goto start;
		}
		perror("Fail write"); // otherwise it's a failure
		close(fd);
		exit(EXIT_FAILURE);
	}

	if(nr != 26){ // if ascii (26 bytes) was not completely written
		perror("Fail write");
		close(fd);
		exit(EXIT_FAILURE);
	}
	
	// close and reopen the file with read and write access
	close(fd);
	fd = open("data.txt", O_RDWR);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}

	off_t ret;
	ret = lseek(fd, 0, SEEK_END); // goes to the end of the file
	if(ret == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf("Current size: %ld\n", ret); // lseek returns the position in bytes,
					    // hence ending position is the same as file lenght in bytes

	// truncating to 10 bytes
	int tr = ftruncate(fd, 10);
	if(tr == -1){
		perror("Fail truncate");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// and rechecking the size
	ret = lseek(fd, 0, SEEK_END);
	if(ret == (off_t) - 1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf("Truncated size: %ld\n", ret);

	// rewinding 
	ret = lseek(fd, 0, SEEK_SET);
	if(ret == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}


	// printing to stdout
	ssize_t r;
	char a;// to read into and write from
	while( (r = read(fd,&a, sizeof(char))) > 0){ // reading char by char
		nr = write(1, &a, r); // 1 stands as constant for stdout
		if(r != nr || nr == -1){ // if number of bytes read and written are different, or write failed
			perror("Fail write");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
	if(r == -1){
		perror("Fail read");
	}

	close(fd);

	return 0;
}
