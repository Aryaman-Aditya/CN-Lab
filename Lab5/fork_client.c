#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];
    char msg[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed");
        close(sock);
        exit(1);
    }

    printf("Connection successful\n");

    while (1) {
        printf("Enter message to send: ");
        if (!fgets(msg, sizeof(msg), stdin)) {
            break;
        }

        msg[strcspn(msg, "\r\n")] = '\0';

        if (strcmp(msg, "exit") == 0 || strcmp(msg, "close") == 0) {
            send(sock, msg, strlen(msg), 0);
            shutdown(sock, SHUT_RDWR);
            break;
        }

        send(sock, msg, strlen(msg), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) {
            printf("Server closed the connection.\n");
            break;
        }

        buffer[n] = '\0';
        printf("Data received: %s\n", buffer);
    }

    close(sock);
    return 0;
}