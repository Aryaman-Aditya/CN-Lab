#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0){
        printf("Error in socket creation\n");
        return 1;
    }

    if(argc < 3){
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        close(sockfd);
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int c1 = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c1 < 0){
        printf("Error in connection\n");
        close(sockfd);
        return 1;
    }

    printf("Connection successful\n");

    char msg[1024];
    char buffer[1024];

    while(1){
        printf("message to send: ");
        if(!fgets(msg, sizeof(msg), stdin)) break;
        msg[strcspn(msg, "\n")] = '\0';

        if(send(sockfd, msg, strlen(msg)+1, 0) < 0){
            printf("Error in sending\n");
            break;
        }

        if(strcmp(msg, "close") == 0){
            close(sockfd);
            break;
        }

        ssize_t rec_size = recv(sockfd, buffer, sizeof(buffer), 0);
        if(rec_size <= 0){
            printf("Connection closed by server\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);
    }

    close(sockfd);
    return 0;
}