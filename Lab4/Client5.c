#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
//client sends roll,name, marks of 3 subs. Server returns % and average mark and grade.



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

    struct student{
        char name[100];
        int roll;
        int marks[3];
    } s1;

    int roll,M1,M2,M3;
    printf("Enter roll number: ");
    scanf("%d", &s1.roll);
    printf("Enter marks of 3 subjects: ");
    scanf("%d %d %d", &s1.marks[0], &s1.marks[1], &s1.marks[2]);
    printf("Enter name: ");
    scanf("%s", s1.name);
    
    ssize_t send_size;
    send_size = send(sockfd, &s1, sizeof(s1), 0); 

    ssize_t rec_size;
    struct result{
        int total;
        double percentage;
        int average;
        char grade;
    } r1;

    rec_size = recv(sockfd, &r1, sizeof(r1), 0);
    printf("Roll number: %d\n", s1.roll);
    printf("Name: %s\n", s1.name);
    printf("Total marks: %d\n", r1.total);
    printf("Average marks: %d\n", r1.average);
    printf("Percentage: %.2f\n", r1.percentage);
    printf("Grade: %c\n", r1.grade);
    
    close(sockfd);
}