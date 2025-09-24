#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // needed for wait() and waitpid()

int main() {
    int status, ret_val;
    pid_t child1, child2;

    // First child
    switch (child1 = fork()) {
        case -1:
            perror("Fork failed");
            exit(EXIT_FAILURE);

        case 0: // child1
            printf("Child 1, pid = %d, Parent pid = %d. I exit with status 9\n", getpid(), getppid());
            sleep(5);
            exit(9);

        default: // parent
            printf("I am the parent, pid = %d. Created Child1 with pid = %d\n", getpid(), child1);
            wait(NULL); // wait for any child
            printf("Child1 exited\n");
            break;
    }

    // Second child
    switch (child2 = fork()) {
        case -1:
            perror("Fork failed");
            exit(EXIT_FAILURE);

        case 0: // child2
            printf("I am Child 2, pid = %d. My parent's pid is %d. I exit with 19\n", getpid(), getppid());
            sleep(2);
            exit(19);

        default: // parent
            printf("I am the parent, pid = %d. Created Child 2 with pid = %d\n", getpid(), child2);
            status = waitpid(child2, &ret_val, 0); // wait for child2 to exit
            if (status == -1) {
                perror("waitpid failed");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(ret_val)) { // if child 2 has really exited with an exit status
                printf("I am the parent. Child 2, pid = %d, exited with status %d\n", child2, WEXITSTATUS(ret_val));
            }
            break;
    }

    return 0;
}

