//Client for TCP connection
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
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //OR = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9090);

    int c1 = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    socklen_t len = sizeof(server_addr);
    ssize_t send_size;

    printf("Enter string:");
    char string[1024];
    scanf("%s", &string);
    send_size = send(sockfd, string, strlen(string), 0);

    ssize_t rec_size;
    char buffer[1024];
    rec_size = recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Reversed string : %s\n", buffer);

    close(sockfd);
}