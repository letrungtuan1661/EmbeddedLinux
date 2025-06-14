#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>  
#include <netinet/in.h>    
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in svaddr, claddr;
    int port_no, socket_sd, len;
    long numBytes;
    char recbuf[100], sendbuf[100];
    char claddrStr[20];

    if (argc < 2) {
        printf("No port provided : ./server <port number>\n");
        exit(EXIT_FAILURE);
    } else {
        port_no = atoi(argv[1]);
    }

    memset(&svaddr, 0, sizeof(struct sockaddr_in)); 
    len = sizeof(struct sockaddr_in);

    // Create server socket
    socket_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = INADDR_ANY;
    svaddr.sin_port = htons(port_no);

    // Assign the socket to its address
    if (bind(socket_sd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in)) == -1){
        printf("Bind failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Start listening on server\n");
	
    while(1) {
        memset(sendbuf, '0', 100);
        memset(recbuf, '0', 100);

        // Receive from client
        numBytes = recvfrom(socket_sd, recbuf, 100, 0, (struct sockaddr *) &claddr, &len);
		if (numBytes == -1){
            printf("Receive failed!\n");
            exit(EXIT_FAILURE);
        }
			
		if (inet_ntop(AF_INET, &claddr.sin_addr, claddrStr, 20) == NULL) 
			printf("Couldn't convert client address to string\n"); 
		else 
			printf("Server received %ld bytes from (%s, %u)\n", (long) numBytes, claddrStr, ntohs(claddr.sin_port)); 
			
        // Server respond
        printf("Please respond the message : ");
        fgets(sendbuf, 100, stdin); // Get string from keyboard

		if (sendto(socket_sd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *) &claddr, len) == -1){
			printf("Send failed!\n");
            exit(EXIT_FAILURE);
        }
	}
}