#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    //clear previous alive process
    signal(SIGCHLD, SIG_IGN);
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(1);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client, &len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            close(client_fd);
            continue;
        }

        if (pid == 0) {
            close(server_fd);

            char buffer[1024];
            int n;

            while ((n = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
                buffer[n] = '\0';// Null-terminate the received data
                printf("Data received: %s\n", buffer);

                if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "close\n") == 0 ||
                    strcmp(buffer, "exit") == 0 || strcmp(buffer, "close") == 0) {
                    break;
                }

                send(client_fd, buffer, n, 0);
            }

            close(client_fd);
            exit(0);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}