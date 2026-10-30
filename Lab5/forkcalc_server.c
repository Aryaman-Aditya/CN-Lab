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
            char response[1024];
            int n;

            while (1) {
                if ((n = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
                    printf("Client closed the connection.\n");
                    break;
                }

                buffer[n] = '\0';
                printf("Equation received: %s\n", buffer);

                if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "close") == 0) {
                    break;
                }

                int a, b, result;
                char op;
                int valid = sscanf(buffer, "%d %c %d", &a, &op, &b);

                if (valid != 3) {
                    snprintf(response, sizeof(response), "Invalid expression");
                } else {
                    switch (op) {
                        case '+':
                            result = a + b;
                            snprintf(response, sizeof(response), "%d", result);
                            break;
                        case '-':
                            result = a - b;
                            snprintf(response, sizeof(response), "%d", result);
                            break;
                        case '*':
                            result = a * b;
                            snprintf(response, sizeof(response), "%d", result);
                            break;
                        case '/':
                            if (b == 0) {
                                snprintf(response, sizeof(response), "Division by zero");
                            } else {
                                result = a / b;
                                snprintf(response, sizeof(response), "%d", result);
                            }
                            break;
                        default:
                            snprintf(response, sizeof(response), "Invalid operator");
                            break;
                    }
                }

                send(client_fd, response, strlen(response), 0);
            }

            close(client_fd);
            exit(0);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}