#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <1 for ls | 2 for date>\n", argv[0]);
        return 1;
    }

    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"date", NULL};

    if (fork() == 0) {
        printf("Inside the child process\n"); 
        if (argv[1][0] == '1') {
            execvp(cmd1[0], cmd1);  // runs 'ls -l'
            // printf("Executing child process\n");   // Never called
        } else if (argv[1][0] == '2') {
            execvp(cmd2[0], cmd2);  // runs 'date'
            // printf("Executing child process\n");   // Never called
        } else {
            printf("Invalid option.\n");
            exit(1);
        }
    }
    else {
        printf("Inside the parent process\n"); 
        while(1);
    }
    return 0;
}

/*
    Giải thích: sau khi exec được tiến trình con gọi, exec sẽ thay thế trực tiếp A
    Trong khi đó, tiến trình cha vẫn chạy bình thường
*/