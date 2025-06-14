#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    static int sigint_count = 0;
    sigint_count++;
    printf("SIGINT received (%d/3)\n", sigint_count);
    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting...\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, handle_sigint);

    while (1) {
        sleep(1);
    }

    return 0;
}

/* If ignore SIGINT, Ctrl+C will no longer terminate the process, as the signal is discarded.*/