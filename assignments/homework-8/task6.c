#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(){

	// opening/creating the file
	int fd = open("numbers.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}
	
	// writing lines 0\n to 9\n
	char *line;
	ssize_t nb_write;
	for(int i = 1; i < 10; i++){
		char c = '0' + i;
		nb_write = write(fd, &c, 1);
		if(nb_write < 0){
			perror("Fail write");
			close(fd);
			exit(EXIT_FAILURE);
		}
		nb_write = write(fd, "\n", 1);
		if(nb_write != 1){
			perror("Fail write");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}

	nb_write = write(fd, "10\n", 3); // writing 10 separately to avoid int to char conversion
	if(nb_write != 3){
		perror("Fail write");
		close(fd);
		exit(EXIT_FAILURE);
	}

	if(close(fd) == -1){
		perror("Fail close");
		exit(EXIT_FAILURE);
	}


	// reopening the file
	fd = open("numbers.txt", O_RDWR);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}

	off_t pos; // offset
	char b; // to read into
	ssize_t nb_read; // number of bytes read
	int nb_nl = 0; // number of new lines read
		     
	while((nb_read = read(fd, &b, 1)) > 0){
		if(b == '\n'){
			nb_nl++;
		}
		if(nb_nl == 3) break; 
	}
	// the position currently pointing to the start of 4th line

	if(nb_read < 0){
		perror("Fail read");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// seeking the start of the 4th line
	pos = lseek(fd, 0, SEEK_CUR);
	if(pos == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// moving to the start of the 5th line to copy from the correct place
	while(read(fd, &b, 1) == 1){
		if(b == '\n'){
			break;
		}
	}
	// seeking the start of the 5th line
	off_t start5 = lseek(fd, 0, SEEK_CUR);

	off_t end = lseek(fd, 0, SEEK_END);
	if(end == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// the size the bytes to copy to be shifted
	ssize_t rem_size = end - start5;
	char *temp = malloc(rem_size);
	if(!temp){
		perror("Fail malloc");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// moving to line 5 to start copying
	if(lseek(fd, start5, SEEK_SET) == -1){
		perror("Fail lseek");
		close(fd);
		free(temp);
		temp = NULL;
		exit(EXIT_FAILURE);
	}

	// copying lines 5 to 10
	nb_read = read(fd, temp, rem_size);
	if(nb_read < 0){
		perror("Fail read");
		close(fd);
		free(temp);
		temp = NULL;
		exit(EXIT_FAILURE);
	}

	// moving back to 4th line to write 100
	if(lseek(fd, pos, SEEK_SET) == -1){
		perror("Fail lseek");
		close(fd);
		free(temp);
		temp = NULL;
		exit(EXIT_FAILURE);
	}

	if(write(fd, "100\n", 4) != 4){
		perror("Fail write");
		close(fd);
		free(temp);
		temp = NULL;
		exit(EXIT_FAILURE);
	}

	// writing from the copied buffer
	if(write(fd, temp, nb_read) != nb_read){
		perror("Fail write");
		close(fd);
		free(temp);
		temp = NULL;	
		exit(EXIT_FAILURE);
	}

	free(temp);
	temp = NULL;

	if(lseek(fd, 0, SEEK_SET) == -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}

	char outbuf[64];
	while((nb_read = read(fd, outbuf, sizeof(outbuf))) > 0){
		if(write(1, outbuf, nb_read) != nb_read){
			perror("Fail write");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}

	if(nb_read < 0){
		perror("Fail read");
		close(fd);
		exit(EXIT_FAILURE);
	}

	close(fd);

	return 0;
}
