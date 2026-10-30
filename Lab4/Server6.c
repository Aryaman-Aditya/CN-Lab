#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int MAX(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

int MIN(int arr[], int n){
    int min = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

int SUM(int arr[], int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int Avg(int arr[], int n){
    int sum = SUM(arr, n);
    return sum/n;
}

int EvenCount(int arr[], int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] % 2 == 0){
            count++;
        }
    }
    return count;
}

int OddCount(int arr[], int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] % 2 != 0){
            count++;
        }
    }
    return count;
}



int main(){
    int sockfd, b1;
    struct sockaddr_in server,client;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM,0);


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; //OR = inet_addr("127.1.0.0");
    server.sin_port = htons(9090);

    b1 = bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    listen(sockfd, 5); //server will listen for 5 connections at a time.

    socklen_t len = sizeof(client);
    int clientSocket = accept(sockfd, (struct sockaddr*)&client, &len); //Accepts request from client in front of backlog queue
    printf("Connection establised to client \n");

    ssize_t rec_size;
    int buffer[1024];
    rec_size = recv(clientSocket, buffer, sizeof(buffer), 0); //Receive data
    printf("Array is: ");
    for(int i = 0; i < rec_size/sizeof(int); i++){
        printf("%d ", buffer[i]);
    }
    printf("\n");
    int result[6];
    result[0] = MAX(buffer, rec_size/sizeof(int));
    result[1] = MIN(buffer, rec_size/sizeof(int));
    result[2] = SUM(buffer, rec_size/sizeof(int));
    result[3] = Avg(buffer, rec_size/sizeof(int));
    result[4] = EvenCount(buffer, rec_size/sizeof(int));
    result[5] = OddCount(buffer, rec_size/sizeof(int)); 

    ssize_t send_size;
    send_size = send(clientSocket, result, sizeof(result), 0); 

    close(clientSocket);
    close(sockfd);

}