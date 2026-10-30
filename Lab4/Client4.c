#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//client sends string. Server returns count of vowel consonant digit space and special char.
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
    char string[1024];
    printf("Enter string: ");
    scanf(" %[^\n]s", string); 
    send_size = send(sockfd, string, strlen(string)+1, 0);

    ssize_t rec_size;
    int result[5];
    rec_size = recv(sockfd, result, sizeof(result), 0);
    printf("Vowels: %d\nConsonants: %d\nDigits: %d\nSpaces: %d\nSpecial Characters: %d\n", result[0], result[1], result[2], result[3], result[4]); // Receiving result from server

    close(sockfd);

}