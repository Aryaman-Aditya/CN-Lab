//connect(): Send a connection request to server.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    int sockfd;
    struct sockaddr_in server;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(9090);

    //connection request to server.
    int c1 = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c1 < 0){
        printf("Error in connection\n");
    }
    else{
        printf("Connection successful\n");
    }

    socklen_t len = sizeof(server);
    ssize_t send_size;
    char *msg = "Hello from client";
    send_size = send(sockfd, msg, strlen(msg)+1, 0); //Sending message to client

    ssize_t rec_size;
    char buffer[1024];
    rec_size = recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Data received of size %ld \n data is: %s\n", rec_size, buffer); //Receiving reply

    close(sockfd);



}