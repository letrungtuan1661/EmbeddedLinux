#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigtstp(int sig) {
    printf("SIGTSTP ignored\n");
}

int main() {
    // Ignore Ctrl+Z
    signal(SIGTSTP, handle_sigtstp);

    while (1) {
        printf("Running... press Ctrl+Z to test ignoring SIGTSTP.\n");
        sleep(2);
    }

    return 0;
}

/* If you don’t handle SIGTSTP, pressing Ctrl+Z will suspend the process (stop it temporarily. 
   By ignoring SIGTSTP, the process avoids being suspended, allowing it to keep running normally. */