//listen(int sockfd, int backlog): Makes the server wait and listen for connection requests.
//backlog: No. of connections server will connect with at a time. Decline requests if connections are more than backlog value.

//accept(): Accept the connection request. 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    int sockfd, b1;
    struct sockaddr_in server,client;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM,0);


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; //OR = inet_addr("127.1.0.0");
    server.sin_port = htons(9090);

    b1 = bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    listen(sockfd, 5); //server will listen for 5 connections at a time.

    socklen_t len = sizeof(client);
    int clientSocket = accept(sockfd, (struct sockaddr*)&client, &len); //Accepts request from client in front of backlog queue
    printf("Connection establised to client");

    //Accept() opens a dedicated socket for the connection between the client and server.

    //Make sure to use dedicated socket for sending receiving.
    //Note: this dedicated socket must be closed as well.


    char buffer[1024];
    ssize_t rec_size;
    rec_size = recv(clientSocket, buffer, sizeof(buffer), 0); //Receive data from client
    //Since the address is known from listen & accept, no need to pass sock addr in recv
    printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);
    //recv vs recvfrom: recvfrom has two additional parameter: sender address and its length.


    ssize_t send_size;
    char *msg = "Hello from TCP server";
    send_size = send(clientSocket, msg, strlen(msg)+1, 0); //Send data to client
    //similar to recv, send also has 2 less parameters than sendto().


    close(clientSocket);//If not closed, the connection remains alive unexpectedly and leak resources.
    //these sockets can stay alive even after main socket is closed.
    close(sockfd);
    

    return 0;
}