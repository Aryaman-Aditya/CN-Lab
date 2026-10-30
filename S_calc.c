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


    b1 = bind(sockfd,  (struct sockaddr*)&server, sizeof(server));
    printf("\nPort no: %d\n IP address: %s\n", ntohs(server.sin_port), inet_ntoa(server.sin_addr)); //ntohs() converts port number from network byte order to host byte order. inet_ntoa() converts IP address from binary to string format.
    char buffer[1024];
    socklen_t len = sizeof(client);
    ssize_t rec_size;
    rec_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&(client) , &len);
    printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);
    //Server calculates expression and return value of expression to client
    ssize_t send_size;
    if(buffer[1] == '+'){
        int a = buffer[0] - '0';
        int b = buffer[2] - '0';
        int c = a + b;
        char result[10];
        sprintf(result, "%d", c);
        send_size = sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&(client), len);
    }
    else if(buffer[1] == '-'){
        int a = buffer[0] - '0';
        int b = buffer[2] - '0';
        int c = a - b;
        char result[10];
        sprintf(result, "%d", c);
        send_size = sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&(client), len);
    }
    else if(buffer[1] == '*'){
        int a = buffer[0] - '0';
        int b = buffer[2] - '0';
        int c = a * b;
        char result[10];
        sprintf(result, "%d", c);
        send_size = sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&(client), len);
    }
    else if(buffer[1] == '/'){
        int a = buffer[0] - '0';
        int b = buffer[2] - '0';
        if(b == 0){
            char result[] = "Division by zero error";
            send_size = sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&(client), len);
        }
        else{
            float c = (float)a / (float)b;
            char result[10];
            sprintf(result, "%.2f", c);
            send_size = sendto(sockfd, result, sizeof(result), 0, (struct sockaddr *)&(client), len);
        }

        close(sockfd);
    }
    return 0;
}