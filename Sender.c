#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> //Required for inet_addr() function. converts IP address from string to binary form. 
//inet_ntoa() converts IP address from binary to string form.

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(int argc, char *argv[]){
    int sockfd,b1;
    struct sockaddr_in server,client;
    int socket(int domain,int type, int protocol);
    sockfd = socket( AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0){
        printf("Error in socket creation\n");
        return 1;
    }

    if(argc < 5){
        printf("Usage: %s <my_ip> <my_port> <peer_ip> <peer_port>\n", argv[0]);
        return 1;
    }

    server.sin_family = AF_INET;
    int port = atoi(argv[2]);
    server.sin_port = htons(port);
    int IP = inet_addr(argv[1]);
    server.sin_addr.s_addr = IP;
    
    b1= bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    if(b1 < 0){
        printf("Error in binding\n");
        close(sockfd);
        return 1;
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(atoi(argv[4]));
    client.sin_addr.s_addr = inet_addr(argv[3]);

    ssize_t send_size;
    char buffer[1024];
    char msg[1024];
    while(1){
        printf("message to send: ");
        if (!fgets(msg, sizeof(msg), stdin)) break;
        msg[strcspn(msg, "\n")] = '\0';
        send_size = sendto(sockfd, msg, strlen(msg)+1, 0, (struct sockaddr *)&client , sizeof(client));

        if(strcmp(msg, "exit") == 0){
            close(sockfd);
            break;
        }
        ssize_t rec_size;
        socklen_t len = sizeof(client);
        rec_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&(client) , &len);
        if(rec_size > 0){
            buffer[strcspn(buffer, "\n")] = '\0';
            printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);

            if(strcmp(buffer, "exit") == 0){
                close(sockfd);
                break;
            }
        }
    }
}