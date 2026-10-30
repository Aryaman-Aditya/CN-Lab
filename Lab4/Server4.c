#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//Server displays count of vowel consonant digit special char and space in string

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

    char buffer[1024];
    ssize_t rec_size;
    rec_size = recv(clientSocket, buffer, sizeof(buffer), 0); 
    printf("String received from client: %s\n", buffer);

    int v = 0, c = 0, d = 0, s = 0, spC = 0;

    for(int i=0; buffer[i] != '\0'; i++){
        char ch = buffer[i];
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || 
               ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){
                v++;
            }
            else{
                c++;
            }
        }
        else if(ch >= '0' && ch <= '9'){
            d++;
        }
        else if(ch == ' '){
            s++;
        }
        else{
            spC++;
        }
    }
    int result[5] = {v, c, d, s, spC};
    send(clientSocket, result, sizeof(result), 0); //Send result 

    close(clientSocket);
    close(sockfd);

}