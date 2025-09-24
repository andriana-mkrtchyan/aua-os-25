#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	pid_t child;
	child = fork();

	if (child < 0){
		perror("Fork failed");
		return -1;
	}
	if(child == 0){
		printf("I am the child, pid = %d. My parent is %d. I will sleep, then exit ...\n", getpid(), getppid());
		sleep(10); // stopping the child to manage to see the status
	}
	else{
		wait(NULL); // making the parent wait for the child and erasing child process safely
		printf("I am the parent, pid = %d, my child is %d\n", getpid(), child);
		sleep(20); // stopping the parent to manage to see the process status 
	}

	return 0;
}
