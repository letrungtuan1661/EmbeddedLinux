#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() 
{
    int fd; 
    const char *data = "This is Exercise1\n";
    
    // fd = open("ex1.txt", O_WRONLY | O_CREAT);  // without O_APPEND flag
    fd = open("ex1.txt", O_WRONLY | O_APPEND | O_CREAT);           
    if (-1 == fd) { 
	    printf("open() ex1.txt failed\n");
    }

    // Seek to beginning
    lseek(fd, 0, SEEK_SET);

    // Write data
    write(fd, data, strlen(data));

    close(fd);
    return 0;
}

/*
    Trả lời: O_APPEND luôn ghi vào cuối file
    cho dù trước đó đã dịch con trỏ lên đầu file.
*/