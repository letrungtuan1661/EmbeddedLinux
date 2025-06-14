#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <unistd.h>
		
void client_handle(int client_sd)
{
    int numb_write, numb_read;
    char recvbuff[100];
    char sendbuff[100];

    while (1) {
        memset(sendbuff, '0', 100);
	   	memset(recvbuff, '0', 100);
        printf("Please enter the message : ");
        fgets(sendbuff, 100, stdin);

        // Write to server
        numb_write = write(client_sd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1){   
            printf("Write to server failed!\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", sendbuff, 4) == 0) {
            break;
        }
		
        // Read from server
        numb_read = read(client_sd, recvbuff, sizeof(recvbuff));
        if (numb_read == -1){
            printf("Read from server failed!\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", recvbuff, 4) == 0) {
            break;
        }
        printf("\nMessage from Server: %s\n",recvbuff);   
    }
    close(client_sd); 
}

int main(int argc, char *argv[])
{
    int portno, client_sd;
    struct sockaddr_in client_addr;
	
    if (argc < 3) {
        printf("Not enough info : ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
    portno = atoi(argv[2]);
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
	
    // Create client socket
    client_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize client address
    client_addr.sin_family = AF_INET;
    client_addr.sin_port   = htons(portno);
    if (inet_pton(AF_INET, argv[1], &client_addr.sin_addr) == -1){
        printf("Inet_pton failed!\n");
        exit(EXIT_FAILURE);
    }
	
    // Connect to server
    if (connect(client_sd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1){
        printf("Connect to server failed!\n");
        exit(EXIT_FAILURE);
    }
    client_handle(client_sd);
    return 0;
}