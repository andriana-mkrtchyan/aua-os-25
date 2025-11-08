#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(){

	// opening the file
	int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}

	// writing to start
	printf("Writing to the start of the file...\n");
	char *word = "START";
	ssize_t nb = write(fd, word, 5*sizeof(char) );
	if(nb < 0){
		perror("Fail write");
		close(fd);
		exit(EXIT_FAILURE);
	}
	
	// skiiping forward 1 MiB
	off_t pos = lseek(fd, 1024*1024, SEEK_CUR); // write automatically moved the offset forward
						    // so SEEK_CUR now points to the pos after START
	if(pos == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// writing to the end
	printf("Writing to the end of the file...\n");
	word = "END";
	nb = write(fd, word, 3*sizeof(char));
	if(nb < 0){
		perror("Fail write");
		close(fd);
		exit(EXIT_FAILURE);
	}

	// closing the file
	if(close(fd) == -1){
		perror("Fail close");
		exit(EXIT_FAILURE);
	}

	// reopening and checking the size
	fd = open("sparse.bin", O_RDONLY);
	if(fd == -1){
		perror("Fail open");
		exit(EXIT_FAILURE);
	}
	pos = lseek(fd, 0, SEEK_END);
	if(pos == (off_t) -1){
		perror("Fail lseek");
		close(fd);
		exit(EXIT_FAILURE);
	}

	printf("File size: %ld\n", pos);

	if(close(fd) == -1){
		perror("Fail close");
		exit(EXIT_FAILURE);
	}
	
	// On my PC, the file appeared to be 1048584 bytes, i.e. over 1MiB, but disk usage is small,
	// because sparse files attempt to use file system space more efficiently.
	// 
	// Sparse files conserve disk space by only allocating physical blocks for actual data,
	// not for holes filled with zeros. Filesystem stores only metadata describing the existence
	// of those zeros instead of the actual blaank data. When a porcess reads the file those 
	// zero byte blovks get generated dynamically as opposed to being stored on physical storage.
	//
	// Hence, the disk usage is much smaller than the apparent size.

	return 0;
}
