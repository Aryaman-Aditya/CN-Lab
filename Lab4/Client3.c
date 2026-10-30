#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//client sends option then integers.
int main(){
    int sockfd;
    struct sockaddr_in server;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd < 0){
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(9090);

    //connection request to server.
    int c1 = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c1 < 0){
        perror("connect");
        return 1;
    }
    else{
        printf("Connection successful\n");
    }

    socklen_t len = sizeof(server);
    ssize_t send_size;

    char buffer[1024];
    recv(sockfd, buffer, sizeof(buffer), 0); //Receive menu from server
    printf("%s", buffer);

    int choice, num1, num2;
    printf("Enter choice (1-4): ");
    scanf("%d", &choice);
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Send the choice and numbers to the server
    int data[3] = {choice, num1, num2};
    send_size = send(sockfd, data, sizeof(data), 0);

    ssize_t rec_size;
    double result;
    rec_size = recv(sockfd, &result, sizeof(result), 0);
    printf("Result is: %.2f\n", result); // Receiving result from server

    close(sockfd);
}