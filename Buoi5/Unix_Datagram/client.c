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
	struct sockaddr_un svaddr;
    int client_sd;
    ssize_t numBytes;
    char recvbuff[100];
    char sendbuff[100];
    
    // Create client socket
    client_sd = socket(AF_UNIX, SOCK_DGRAM, 0);      
    if (client_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }
	
	memset(&svaddr, 0, sizeof(struct sockaddr_un)); 

    // Initialize client address
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

	// Send to server
    printf("Please enter the message : ");
    fgets(sendbuff, 100, stdin);

	if(sendto(client_sd, sendbuff, sizeof(sendbuff), 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1){
        printf("Send to server failed!\n");
        exit(EXIT_FAILURE);
    }

    // Receive from server    
	numBytes = recvfrom(client_sd, recvbuff, sizeof(recvbuff), 0, NULL, NULL);
	if (numBytes == -1){
		printf("Read from server failed!\n");
        exit(EXIT_FAILURE);
    } else
		printf("Response : %s\n", recvbuff);
    
    return 0;
}