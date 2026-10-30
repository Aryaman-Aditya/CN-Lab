#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//Client send n integers. Server sorts and returns. n is given by user
int main(){
    int sockfd;
    struct sockaddr_in server;
    int socket(int domain, int type, int protocol);
    sockfd = socket(AF_INET, SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(9090);

    //connection request to server.
    int c1 = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(c1 < 0){
        printf("Error in connection\n");
    }
    else{
        printf("Connection successful\n");
    }

    socklen_t len = sizeof(server);
    ssize_t send_size;
    int n;
    printf("Enter number of integers to send:");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the integers:");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    send_size = send(sockfd, arr, n * sizeof(int), 0);

    ssize_t rec_size;
    int sorted_arr[n];
    rec_size = recv(sockfd, sorted_arr, sizeof(sorted_arr), 0);
    printf("Sorted integers received of size %ld \n data is: ", rec_size);
    for(int i=0; i<n; i++){
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");

    close(sockfd);


}