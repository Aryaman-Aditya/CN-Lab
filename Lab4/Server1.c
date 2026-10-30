//Server returns reverse of string. TCP
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    int sockfd,b;
    struct sockaddr_in server_addr,client_addr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //OR = inet_addr("127.1.0.0");
    server_addr.sin_port = htons(9090);

    b= bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(sockfd, 5); 

    socklen_t len = sizeof(client_addr);
    int clientSocket = accept(sockfd, (struct sockaddr*)&client_addr, &len); 
    printf("Connection establised to client \n");

    char buffer[1024];
    ssize_t rec_size;
    rec_size = recv(clientSocket, buffer, sizeof(buffer), 0); 
    printf("Received string : %s\n", buffer);

    //Reverse the string
    int n = strlen(buffer);
    for(int i=0; i<n/2; i++){
        char temp = buffer[i];
        buffer[i] = buffer[n-i-1];
        buffer[n-i-1] = temp;
    }

    ssize_t send_size;
    send_size = send(clientSocket, buffer, strlen(buffer), 0);
    close(clientSocket);
    close(sockfd);
    return 0;


}