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
    int pipe1[2], pipe2[2];
    pid_t child1, child2;
    char buffer[100];
    const char *message = "Data from parent";

    pipe(pipe1); // Pipe from parent to child1
    pipe(pipe2); // Pipe from child1 to child2

    if ((child1 = fork()) == 0) {
        // Child 1
        close(pipe1[1]); // close write end of pipe1
        read(pipe1[0], buffer, sizeof(buffer));
        strcat(buffer, " + modified by child1");

        close(pipe1[0]);
        close(pipe2[0]); // close read end of pipe2
        write(pipe2[1], buffer, strlen(buffer));
        close(pipe2[1]);
        exit(0);
    }

    if ((child2 = fork()) == 0) {
        // Child 2
        close(pipe2[1]); // close write end of pipe2
        read(pipe2[0], buffer, sizeof(buffer));
        printf("Child2 received: %s\n", buffer);
        close(pipe2[0]);
        exit(0);
    }

    // Parent process

    // Prevent zombie process 
    signal(SIGCHLD, func);
    
    close(pipe1[0]); // close read end of pipe1
    write(pipe1[1], message, strlen(message));
    close(pipe1[1]);

    // Close unused pipe ends in parent
    close(pipe2[0]);
    close(pipe2[1]);

    return 0;
}