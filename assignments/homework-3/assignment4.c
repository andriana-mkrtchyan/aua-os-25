#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	pid_t child1, child2;
	int status;

	child1 = fork(); // creating first child process
	if(child1 < 0){ // error checking
		perror("Child1 fork failed.\n");
		return -1;
	} 
	else if(child1 == 0){ // first child
		printf("Child1 successfully created, pid = %d, parent = %d.\n", getpid(), getppid());
		exit(11); // child1 exit status
	}

	// Only parent creates second child
	child2 = fork(); // creating second child process
	if(child2 < 0){ // error checking
		perror("Child2 fork failed.\n");
		return -1;
	} 
	else if(child2 == 0){ // second child
		printf("Child2 successfully created, pid = %d, parent = %d.\n", getpid(), getppid());
		exit(13); // child2 exit status
	}

	// Parent waits for child1
	waitpid(child1, &status, 0); // wait for child1 to end and store its return value
	if(WIFEXITED(status)){ // if child1 successfully exited
		printf("I am the parent. Child1, pid = %d, terminated with status %d.\n", child1, WEXITSTATUS(status)); // get exit status
	}
	else{
		printf("Error with child1 execution\n");
	}

	// Parent waits for child2
	waitpid(child2, &status, 0); // wait for child2 to end and store its return value
	if(WIFEXITED(status)){ // if child2 successfully exited
		printf("I am the parent. Child2, pid = %d, terminated with status %d.\n", child2, WEXITSTATUS(status)); // get exit status
	}
	else{
		printf("Error with child2 execution\n");
	}

	return 0;
}

