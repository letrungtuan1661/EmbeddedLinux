#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

static void func(int signum)
{
    printf("Child process termination\n");
}

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    const char *message = "Hello from parent";

    pipe(pipefd); // Create pipe
    pid = fork(); // Create child process

    if (pid == 0) {     // Child Process
        close(pipefd[1]); // Close write end
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipefd[0]);
    } else {            // Parent Process
        // Prevent zombie process 
        signal(SIGCHLD, func);
        close(pipefd[0]); // Close read end
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]);
    }

    return 0;
}