#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//Server is calculator. displays menu. 1st input isa choice and then 2 integers from client.
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
    printf("Connection establised to client \n");

    char *msg = "1: Addition\n2: Subtraction\n3: Multiplication\n4: Division\n ";
    send(clientSocket, msg, strlen(msg)+1, 0); //Sends menu

    int buffer[3];
    ssize_t rec_size;
    rec_size = recv(clientSocket, buffer, sizeof(buffer), 0); 

    double result;

    if(buffer[0] == 1){
        result = (double)buffer[1] + buffer[2];
        send(clientSocket, &result, sizeof(result), 0);
    }

    else if(buffer[0] == 2){
        result = (double)buffer[1] - buffer[2];
        send(clientSocket, &result, sizeof(result), 0);
    }

    else if(buffer[0] == 3){
        result = (double)buffer[1] * buffer[2];
        send(clientSocket, &result, sizeof(result), 0);
    }

    else if(buffer[0] == 4){
        if(buffer[2] != 0){
            result = (double)buffer[1] / (double)buffer[2];
            send(clientSocket, &result, sizeof(result), 0);
        }
    }

    else{
        printf("Invalid choice\n");
    }

    close(clientSocket);
    close(sockfd);
}