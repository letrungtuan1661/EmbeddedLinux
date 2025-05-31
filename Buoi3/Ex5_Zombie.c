#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status;

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child (Zombie): PID = %d\n", getpid());
        exit(0); // Child exits immediately
    } else {
        printf("Parent sleeping, not calling wait()... Child becomes zombie\n");
        sleep(30);  // Give time to observe zombie
        wait(&status);
    }

    return 0;
}