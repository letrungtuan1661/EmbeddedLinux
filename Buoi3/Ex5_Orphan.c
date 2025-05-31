#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        sleep(5);  // Wait for parent to exit
        printf("Orphan child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        while(1);  // Keep child alive for observation
    } else {
        printf("Parent exiting. Child will become orphan.\n");
        exit(0);  // Parent exits immediately
    }

    return 0;
}