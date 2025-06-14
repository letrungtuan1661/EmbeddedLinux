#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>  
#include <netinet/in.h>    
#include <arpa/inet.h>
#include <unistd.h>

void server_handle(int new_socket_sd)
{       
    int numb_read, numb_write;
    char sendbuff[100];
    char recvbuff[100];
	
    while (1) {        
        memset(sendbuff, '0', 100);
        memset(recvbuff, '0', 100);

        // Read from client
        numb_read = read(new_socket_sd, recvbuff, 100);
        if(numb_read == -1){
            printf("Read from client failed!\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", recvbuff, 4) == 0) {
            break;
        }
        printf("\nMessage from Client: %s\n", recvbuff);

        // Server respond
        printf("Please respond the message : ");
        fgets(sendbuff, 100, stdin); // Get string from keyboard
        numb_write = write(new_socket_sd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1){
            printf("Write to client failed!\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp("exit", sendbuff, 4) == 0) {
            break;
        }
    }
    close(new_socket_sd);
}

int main(int argc, char *argv[])
{
    int port_no, len;
    int socket_sd, new_socket_sd;
    struct sockaddr_in serv_addr, client_addr;

    if (argc < 2) {
        printf("No port provided : ./server <port number>\n");
        exit(EXIT_FAILURE);
    } else {
        port_no = atoi(argv[1]);
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    len = sizeof(struct sockaddr_in);
    
    // Create socket server
    socket_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_sd == -1){
        printf("Create socket failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY; 

    // Assign the socket to its address
    if (bind(socket_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        printf("Bind failed!\n");
        exit(EXIT_FAILURE);
    }

    // Maximum 5 connections
    if (listen(socket_sd, 5) == -1){
        printf("Listen failed!\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Server listens at port: %d \n....\n", port_no);
		new_socket_sd = accept(socket_sd, (struct sockaddr *)&client_addr, (socklen_t *)&len); 
		if (new_socket_sd == -1){
            printf("Accept failed!\n");
            exit(EXIT_FAILURE);
        }
		printf("Server : got connection \n");
		server_handle(new_socket_sd);
    }

    close(socket_sd);
    return 0;
}