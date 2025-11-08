#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFSIZE 256

int main(){

	printf("Starting...\n");

	// opening the log file
	int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}
	

	printf("File log.txt opened.\n");

	// allocating memory for user line input
	char *buf = malloc(BUFSIZE);
	if(!buf){
		perror("Fail malloc");
		close(fd);
		exit(EXIT_FAILURE);
	}

	size_t len = 0; // length of the line
	char b; // to read into and write from 
	ssize_t nb_read; // number of bytes read

	
	printf("Write a log line:\n");
	
	// reading a line
	while((nb_read = read(0, &b, 1)) > 0){
		if(b == '\n'){
			break;
		}

		// if the length of the line is greater than expected, 
		// expand the buffer size
		if(len + 1 >= BUFSIZE){
			char *tmp = realloc(buf, 2*BUFSIZE);
			if(!tmp){
				perror("Fail realloc");
				close(fd);
				free(buf);
				buf = NULL;
				exit(EXIT_FAILURE);
			}
			buf = tmp;
		}

		buf[len++] = b;
	}

	if(nb_read < 0){
		perror("Fail read");
		close(fd);
		free(buf);
		buf = NULL;
		exit(EXIT_FAILURE);
	}


	buf[len++] = '\n';
	
	// preparing for prepend
	//
	// getting the pid, calculating its length and converting to string
	pid_t pid = getpid();
	size_t len_pid = 0;
	char str_pid[10]; // on my PC, max pid was 4194304, generally, it won't 
			  // be larger than that, so 10 bytes is more than enough 
			  // to count the pid length
	if(pid == 0){ // although this can never happen
		str_pid[len_pid++] = '0';
	}
	else{ 
		pid_t tmp = pid;
		char rev[10]; // use a temporary buffer as digits will be converted to char in
			      // reversed order
		size_t k = 0; // length of the reversed pid
		while(tmp > 0){
			rev[k++] = '0' + (tmp%10); // tmp%10 gives the last digit, 
						   // which we convert to char by adding it to '0'
			tmp /= 10;
		}	
		for(int i = k-1; i >=0; i--){ // write from reversed to the real pid buffer
			str_pid[len_pid++] = rev[i];
		}
	}

	// prepenfing the line
	size_t len_prefix = 7 + len_pid;
	size_t len_line = len_prefix + len;
	char full_line[len_line];


	full_line[0] = 'P';
	full_line[1] = 'I';
	full_line[2] = 'D';
	full_line[3] = '=';
	full_line[4] = '<';
	for(int i = 0; i < len_pid; i++){
		full_line[i + 5] = str_pid[i];
	}
	full_line[len_prefix - 2] = '>';
	full_line[len_prefix - 1] = ':';
	for(int i = 0; i < len; i++){
		full_line[i + len_prefix] = buf[i];
	}


	// getting current the position before writing the new line to the file
	off_t pos = lseek(fd, 0, SEEK_CUR);
	if(pos == (off_t) -1){
		perror("Fail seek");
		close(fd);
		free(buf);
		buf = NULL;
		exit(EXIT_FAILURE);
	}
	printf("Position before append: %ld\n", pos);
	printf("Length of the log line: %ld\n", len_line);

	// writing the log
	ssize_t nb_write = write(fd, full_line, len_line);
	if(nb_write == -1){
		perror("Fail write");
		close(fd);
		free(buf);
		buf = NULL;
		exit(EXIT_FAILURE);
	};


	// checking current position and offset
	pos = lseek(fd, 0, SEEK_CUR);
	if(pos == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		free(buf);
		buf = NULL;
		exit(EXIT_FAILURE);
	}

	printf("Position after append: %ld\n", pos);
	

	return 0;
}
