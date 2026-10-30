//CN LAB DAY 3
//SOCKET PROGRAMMING

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>


int PORT = 8080;
struct sockaddr{ //Generic socket address structure. stores info about the address family and protocol address
    
    unsigned short sa_family; //Address family
    char sa_data[14]; //14 bytes of protocol address
};

struct sockaddr_in{ //Socket address structure for IPv4. Stores info about the address family, port number, and IP address
    
    short sin_family; //Protocol. using IPV4 here
    unsigned short sin_port; //Port number
    struct in_addr sin_addr; //IP address
    char sin_zero[8]; 
};

struct in_addr{ //stores an IP address
    unsigned long s_addr;
};


int main(){
    int socketID, new_Socket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char buffer[1024];
    socketID = socket(AF_INET, SOCK_DGRAM, 0); //Assigning socket. value >0 : success, <0 : failure

    serverAddr.sin_family = AF_INET; //Assign IPv4 protocol
    serverAddr.sin_port = htons(PORT); //host to network short conversion for port number
    serverAddr.sin_addr.s_addr = inet_addr(INADDR_ANY); //takes any address available on OS

    //instead of INADDR_ANY a specific IP address can be used like "10.10.10.10"


    bind(socketID, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); //binds socket address to endpoint
    //int bind >0 : success, <0 : failure
    ssize_t recvfrom(int socketID, void *buf[], size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen); //receives data from a socket
    ssize_t sendto(int socketID, const void *message, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen); //sends data to a socket
    

    return 0;

}