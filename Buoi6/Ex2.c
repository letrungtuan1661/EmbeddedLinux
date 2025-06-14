#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0;

void handle_sigalrm(int sig) {
    seconds++;
    printf("Timer: %d seconds\n", seconds);

    if (seconds < 10) {
        alarm(1);  // rearm the alarm for next second
    } else {
        printf("Timer reached 10 seconds. Exiting...\n");
        exit(0);
    }
}

int main() {
    signal(SIGALRM, handle_sigalrm);
    alarm(1); // trigger every  1 second

    while (1) {
        sleep(1);
    }

    return 0;
}

/* If you don't re-arm the alarm by calling alarm(1) in the handler, the signal will only fire once. */