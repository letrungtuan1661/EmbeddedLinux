#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;      
    int counter = 2;                
    printf("Initial value of counter: %d\n", counter);

    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       // Child process 
            printf("\nIm the child process, counter: %d\n", ++counter);
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
            exit(0);
        } else {                    // Parent process
            printf("\nIm the parent process, counter: %d\n", ++counter);
            printf("My PID is: %d, my child PID is: %d\n", getpid(), child_pid);
            while(1);
        }
    } else {       // return -1 if failed     
        printf("Fork() failed\n");    
    }

    return 0;
}