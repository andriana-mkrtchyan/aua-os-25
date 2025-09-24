i#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	
	pid_t child = fork(); // create a child process
	switch(child){ // this is same as if-else statements, checking the process currently being run
		case -1: // if process creation failed, -1 is returned.
			perror("Fork failed."); // writing to standard error output
			exit(EXIT_FAILURE); // EXIT_FAILURE is a special predefined macros, a return status in 						stdlib.h, usually equals 1
		case 0:
			printf("I am the child. PID: %d, my parent is: %d\n", getpid(), getppid()); 
				//getppid() is the function for getting the parent process id
			exit(EXIT_SUCCESS); // again, a predefined return status, usually 0
		default:
			printf("I am the parent. PID: %d\n", getpid());
			break; // not waiting the child to complete
	}
	return 0;
}
