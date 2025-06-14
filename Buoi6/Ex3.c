#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int signal_count = 0;

void handle_sigusr1(int sig) {
    printf("Child: Received signal from parent (%d/5)\n", ++signal_count);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        signal(SIGUSR1, handle_sigusr1);
        while (signal_count < 5) {
            sleep(1); 
        }
        printf("Child: Exiting after receiving 5 signals.\n");
    } else {
        // Parent process
        for (int i = 0; i < 5; ++i) {
            sleep(2);
            kill(pid, SIGUSR1);  // send signal to child
        }
        wait(NULL);  // wait for child to exit
        printf("Parent: Finished.\n");
    }

    return 0;
}

/* The kill() system call sends a signal to a specific process. */