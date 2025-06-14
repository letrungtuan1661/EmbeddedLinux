#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <unistd.h>

#define BUF_SIZE 10 
#define SOCK_PATH "./sock_stream"

int main(int argc, char *argv[])
{    
	struct sockaddr_un svaddr;
    int client_sd;
    char recvbuff[100];
    char sendbuff[100];
	
    // Create client socket
    client_sd = socket(AF_UNIX, SOCK_STREAM, 0);      
    if (client_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }
	
    memset(&svaddr, 0, sizeof(struct sockaddr_un));

    // Initialize client address
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);
	
    // Connect to server
	if (connect(client_sd, (struct sockaddr*)&svaddr, sizeof(struct sockaddr)) != 0) 
	{ 
        printf("connection with the server failed...\n"); 
        exit(EXIT_FAILURE);
    } 
    else
        printf("connected to the server.\n");
	
	while(1)
	{     
        memset(sendbuff, '0', 100);
	    memset(recvbuff, '0', 100); 

        printf("Please enter the message : ");
        fgets(sendbuff, 100, stdin);
        write(client_sd, sendbuff, sizeof(sendbuff));
        if(read(client_sd, recvbuff, sizeof(recvbuff))) 
			printf("From Server : %s\n", recvbuff); 
    } 
    
    return 0;
}