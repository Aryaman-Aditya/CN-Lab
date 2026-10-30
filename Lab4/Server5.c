#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//Server displays count of vowel consonant digit special char and space in string

struct student{
    char name[100];
    int roll;
    int marks[3];
};

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
    struct student s1;
    rec_size = recv(clientSocket, &s1, sizeof(s1), 0);
    struct result{
        int total;
        double percentage;
        int average;
        char grade;
    } r1;
    r1.total = s1.marks[0] + s1.marks[1] + s1.marks[2];
    r1.average = r1.total / 3;
    r1.percentage = (double)r1.total / 3.0;
    r1.grade = 'C'; // Default grade
    if(r1.total>200){
        r1.grade = 'A';
    }
    else if(r1.total>100){
        r1.grade = 'B';
    }
    else{
        r1.grade = 'C';
    }

    ssize_t send_size;
    send_size = send(clientSocket, &r1, sizeof(r1), 0);

    close(clientSocket);
    close(sockfd);
    

}