
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>  // for errno

void handle_sigint(int sig) {
    printf("SIGINT received.\n");
}

void handle_sigterm(int sig) {
    printf("SIGTERM received. Exiting...\n");
    exit(0);
}

int main() {
    // Set up signal handlers
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    printf("Program started. Press Ctrl+C to send SIGINT or send SIGTERM to exit.\n");

    while (1) {
        fd_set readfds;                      // Declare a set of file descriptors
        FD_ZERO(&readfds);                   // Clear the set (make it empty)
        FD_SET(STDIN_FILENO, &readfds);      // Add STDIN (fd 0) to the set

        struct timeval timeout;
        timeout.tv_sec = 1;  // Wait for 1 second
        timeout.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
        if (ret == -1) {
            if (errno == EINTR) {
                // Interrupted by signal
                continue;
            } else {
                printf("select failed\n");
                break;
            }
        } else if (ret > 0) {
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                char buffer[1024];
                if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                    printf("You entered: %s", buffer);
                }
            }
        }
    }

    return 0;
}
