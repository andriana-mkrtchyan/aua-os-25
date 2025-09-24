#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	pid_t child;
	child = fork(); // creating the child

	if (child < 0){
		perror("Fork failed");
		return -1;
	}
	if(child == 0){ 
		printf("I am the child, pid = %d. My parent is %d. I will soon become a zombie ...\n", getpid(), getppid());
		
	}
	else{
		printf("I am the parent, pid = %d, my child is %d\n", getpid(), child);
		sleep(30); // stopping the parent to manage to run htop and see process states
	}

	return 0;
}
