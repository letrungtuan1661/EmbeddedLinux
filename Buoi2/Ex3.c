#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    const char *filename = "ex3.txt";
    int fd = open(filename, O_WRONLY | O_CREAT);
    if (fd == -1) {
        printf("open() ex3.txt failed\n");
        return 1;
    }

    const char *data = "Data for stat example\n";
    write(fd, data, strlen(data));
    close(fd);

    struct stat st;
    if (stat(filename, &st) == -1) {
        printf("stat failed\n");
        return 1;
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", st.st_size);
    printf("Last file modification: %s", ctime(&st.st_mtime));
    printf("File Type: ");
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:   printf("block device\n");       break;
        case S_IFCHR:   printf("character device\n");   break;
        case S_IFDIR:   printf("directory\n");          break;
        case S_IFIFO:   printf("FIFO/pipe\n");          break;
        case S_IFLNK:   printf("symlink\n");            break;
        case S_IFREG:   printf("regular file\n");       break;
        case S_IFSOCK:  printf("socket\n");             break;
        default:        printf("unknown?\n");
    }
    
    return 0;
}