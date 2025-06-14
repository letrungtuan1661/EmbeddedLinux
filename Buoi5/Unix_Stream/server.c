#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>

#define SOCK_PATH "./sock_stream"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr;
    int server_sd, data_sd, j;
    ssize_t numBytes;
    socklen_t len;
    char sendbuff[100];
    char recvbuff[100];

    // Create server socket
    server_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }

    memset(&svaddr, 0, sizeof(struct sockaddr_un)); 
    
    // Initialize server address
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    // Assign address to server
    if (bind(server_sd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1){
        printf("Bind failed!\n");
        exit(EXIT_FAILURE);
    }
 
    if ((listen(server_sd, 5)) == -1){
        printf("Listen failed!\n");
        exit(EXIT_FAILURE);
    } else
	    printf("start listening on server\n");

	if((data_sd = accept(server_sd, (struct sockaddr*)&svaddr, &len)) == -1){
            printf("Accept failed!\n");
            exit(EXIT_FAILURE);
    }

    while(1) {
        memset(sendbuff, '0', sizeof(sendbuff));
        memset(recvbuff, '0', sizeof(recvbuff));

        if(read(data_sd, recvbuff, sizeof(recvbuff)))
		{
            printf("receive %s\n", recvbuff);
            printf("Please respond the message : ");
            fgets(sendbuff, sizeof(sendbuff), stdin); // Get string from keyboard
			write(data_sd,sendbuff,sizeof(sendbuff));
		}
    }
	close(server_sd);
	remove(SOCK_PATH);
}