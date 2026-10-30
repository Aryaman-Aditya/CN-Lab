#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//



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

    int n;
    printf("Enter number of integers to send: ");
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    ssize_t send_size;
    send_size = send(sockfd, arr, sizeof(arr), 0); //Sending array to server

    ssize_t rec_size;
    int result[6];
    rec_size = recv(sockfd, result, sizeof(result), 0); //Receiving results from
    printf("Max: %d\n", result[0]);
    printf("Min: %d\n", result[1]);
    printf("Sum: %d\n", result[2]);
    printf("Average: %d\n", result[3]);
    printf("Even Count: %d\n", result[4]);
    printf("Odd Count: %d\n", result[5]);

    close(sockfd);

}