#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(int argc, char *argv[]){
    int sockfd, b1;
    struct sockaddr_in server, client;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0){
        printf("Error in socket creation\n");
        return 1;
    }

    if(argc < 2){
        printf("Usage: %s <server_port>\n", argv[0]);
        close(sockfd);
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    b1 = bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(b1 < 0){
        printf("Error in binding\n");
        close(sockfd);
        return 1;
    }

    if(listen(sockfd, 5) < 0){
        printf("Error in listen\n");
        close(sockfd);
        return 1;
    }

    socklen_t len = sizeof(client);
    int clientSocket = accept(sockfd, (struct sockaddr*)&client, &len);
    if(clientSocket < 0){
        printf("Error in accept\n");
        close(sockfd);
        return 1;
    }

    printf("Connection established to client\n");
    printf("Client IP Address: %s\n", inet_ntoa(client.sin_addr));
    printf("Client Port Number: %d\n", ntohs(client.sin_port));

    char buffer[1024];
    char msg[1024];

    while(1){
        ssize_t rec_size = recv(clientSocket, buffer, sizeof(buffer), 0);
        if(rec_size <= 0){
            printf("Connection closed by client\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);

        if(strcmp(buffer, "close") == 0){
            break;
        }

        printf("message to send: ");
        if(!fgets(msg, sizeof(msg), stdin)) break;
        msg[strcspn(msg, "\n")] = '\0';

        if(send(clientSocket, msg, strlen(msg)+1, 0) < 0){
            printf("Error in sending\n");
            break;
        }
    }

    close(clientSocket);
    close(sockfd);
    return 0;
}