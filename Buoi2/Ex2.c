#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Extract information
    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    char mode = argv[3][0];
    char *content = argv[4];
    int fd;

    if (mode == 'r') {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            printf("open() %s failed\n", filename);
            return 1;
        }
        char *buffer = malloc(num_bytes + 1);
        int bytesRead = read(fd, buffer, num_bytes);
        buffer[bytesRead] = '\0';
        printf("Read content: %s\n", buffer);
        free(buffer);
    } else if (mode == 'w') {
        fd = open(filename, O_WRONLY | O_CREAT);
        if (fd == -1) {
            printf("open() %s failed\n", filename);
            return 1;
        }
        write(fd, content, num_bytes);
        printf("Wrote %d bytes.\n", num_bytes);
    } else {
        fprintf(stderr, "Invalid mode: use 'r' or 'w'\n");
        return 1;
    }

    close(fd);
    return 0;
}