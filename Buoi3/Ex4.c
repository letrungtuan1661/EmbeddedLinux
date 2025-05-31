#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s and add exit code!\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    int status, rv;
    int exit_code = atoi(argv[1]);  // Custom exit code

    if (pid < 0) {
        printf("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process exits with a custom code
        printf("Child: Exiting with code %d\n", exit_code);
        exit(exit_code);
    } else {
        // Parent process waits for child
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Parent: Child exited normally with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child did not exit normally\n");
        }
    }

    return 0;
}