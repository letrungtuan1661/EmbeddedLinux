#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SOCK_PATH "./sock_dgram"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int socket_sd, j;
    ssize_t numBytes;
    socklen_t len;
    char recbuf[100], sendbuf[100];

    // Create server socket
    socket_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (socket_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }
    memset(&svaddr, 0, sizeof(struct sockaddr_un)); 
    len = sizeof(struct sockaddr_un);

    // Initialize server address
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    // Assign address to server
    if (bind(socket_sd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1){
        printf("Bind failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("start listening on server\n");
	
    while(1) {
        memset(sendbuf, '0', 100);
        memset(recbuf, '0', 100);

        numBytes = recvfrom(socket_sd, recbuf, sizeof(recbuf), 0, (struct sockaddr *) &claddr, &len);
		if (numBytes == -1){
            printf("Receive failed!\n");
            exit(EXIT_FAILURE);
        }

		// Server respond
        printf("Please respond the message : ");
        fgets(sendbuf, 100, stdin); // Get string from keyboard

		if (sendto(socket_sd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *) &claddr, len) == -1){
			printf("Send failed!\n");
            exit(EXIT_FAILURE);
        }
	}
    close(socket_sd);
	remove(SOCK_PATH);
}