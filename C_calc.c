#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h> //Required for inet_addr() function. converts IP address from string to binary form. 
//inet_ntoa() converts IP address from binary to string form.

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h> //Required for sockaddr_in structure. 

int main(int argc, char *argv[]){
    int sockfd;
    int b1;
    struct sockaddr_in server, client; //Stores server and client address
    

    int socket(int domain, int type, int protocol); 
    //creates an endpoint for communication and returns a descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  //Assigning/Creating socket. value >0 : success, <0 : failure

    if (sockfd < 0) {
        printf("Error in socket creation\n");
    }
    else{
        printf("Socket created successfully\n");
    }

    server.sin_family = AF_INET; //Assign IPv4 protocol
    int port = atoi(argv[1]);
    server.sin_port = htons(port); //host to network short conversion for port number
    server.sin_addr.s_addr = INADDR_ANY; //takes/listens any IP address available on the system

    printf("\nPort no: %d\n IP address: %s\n", ntohs(server.sin_port), inet_ntoa(server.sin_addr)); //ntohs() converts port number from network byte order to host byte order. inet_ntoa() converts IP address from binary to string format.

    ssize_t send_size;
    char *equation = "2+3";
    send_size = sendto(sockfd, equation, strlen(equation)+1, 0, (struct sockaddr *)&server , sizeof(server));
    char buffer[1024];

    socklen_t len = sizeof(client);
    ssize_t rec_size;
    rec_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&(client) , &len);
    printf("Data received of size %ld \n Value of expression is: %s\n", rec_size, buffer);
    
    close(sockfd);
}