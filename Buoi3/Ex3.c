#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handle_sigusr1(int sig) {
    printf("Child received SIGUSR1 signal (signal number: %d)\n", sig);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {                      
        signal(SIGUSR1, handle_sigusr1);                // Child process    
        printf("Child waiting for SIGUSR1...\n");       // Register handler   
        pause();                                        // Blocks until receive (must)
        printf("Child received SIGUSR1. Child exiting.\n");
    } else {                                            // Parent process
        sleep(2);                                       // Wait before sending signal
        printf("Parent sending SIGUSR1 to child (PID: %d)\n", pid);
        kill(pid, SIGUSR1);                             // Sends the signal
    }

    return 0;
}