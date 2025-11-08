#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 512

int main(){

	char sPath[50], dPath[50]; // source and destination file paths
	unsigned int totalCopied = 0;  // roral number of bytes copied
	
	printf("Source file path: ");
	scanf("%49s", sPath);

	printf("Destination file path: ");
	scanf("%49s", dPath);


	int sfd = open(sPath, O_RDONLY); // source file descriptor
					 // opening source file to read from
	if(sfd == -1){
		perror("Fail opening source file");
		exit(EXIT_FAILURE);
	}

	int dfd = open(dPath, O_WRONLY|O_CREAT|O_TRUNC, 0644); // destination foile descriptor
							      // creating (opening if exists) the destination
							      // file to write
	if(dfd == -1){
		perror("Fail opening destination file");
		close(sfd);
		exit(EXIT_FAILURE);
	}


	char buff[BUFSIZE]; // buffer to read into and write from
	ssize_t bRead, bWrite; // to check number of bytes effectively read and written

		
	while((bRead = read(sfd, &buff, BUFSIZE)) > 0){
		// while the number of bytes read is greater than 0, i.e. EOF not reached
		bWrite = write(dfd, &buff, bRead);
		// write to destination and count the number of bytes written

		if(bRead != bWrite){ // if number of bytes written is different from those read
				     // an error has occured 
			perror("Write error");
			close(sfd);
			close(dfd);
			exit(EXIT_FAILURE);
		}
		
		// if no, bWrite bytes were successfully copied
		totalCopied += bWrite;
	}

	if(bRead < 0){
		perror("Read error");
	}

	printf("Number of bytes successfulyy copied: %d.\n", totalCopied);

	close(sfd);
	close(dfd);

	return 0;
}
