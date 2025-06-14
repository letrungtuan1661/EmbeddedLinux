#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{    
	struct sockaddr_in claddr;
    int client_sd, portno;
    ssize_t numBytes;
    char recvbuff[100];
    char sendbuff[100];
	
    // Create client socket
    client_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }
    portno = atoi(argv[2]);
    memset(&claddr, 0, sizeof(struct sockaddr_in));
    memset(sendbuff, '0', 100);
	memset(recvbuff, '0', 100);

    // Initialize client address
    claddr.sin_family = AF_INET;
    claddr.sin_port = htons(portno);
    if(inet_pton(AF_INET, argv[1], &claddr.sin_addr) == -1){
        printf("Inet_pton failed!\n");
        exit(EXIT_FAILURE);
    }

    // Send to server
    printf("Please enter the message : ");
    fgets(sendbuff, 100, stdin);

	if(sendto(client_sd, sendbuff, sizeof(sendbuff), 0,(struct sockaddr *)&claddr, sizeof(struct sockaddr_in)) == -1){
        printf("Send to server failed!\n");
        exit(EXIT_FAILURE);
    }

    // Receive from server
	numBytes = recvfrom(client_sd, recvbuff, sizeof(recvbuff), 0, NULL, NULL);
	if (numBytes == -1){
            printf("Read from server failed!\n");
            exit(EXIT_FAILURE);
    }
	else
		printf("Response : %s\n", recvbuff);
    
    return 0;
}