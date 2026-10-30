#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
	int sockfd;
	int b1;
	struct sockaddr_in server;

	int socket(int domain, int type, int protocol);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		printf("Error in socket creation\n");
	}
	else{
		printf("Socket created successfully\n");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8080);

	int n;
	printf("Enter an integer N: ");
	scanf("%d", &n);

	char msg[32];
	sprintf(msg, "%d", n);

	ssize_t send_size;
	send_size = sendto(sockfd, msg, strlen(msg)+1, 0, (struct sockaddr *)&server, sizeof(server));

	char buffer[1024];
	socklen_t len = sizeof(server);
	ssize_t rec_size;
	rec_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, &len);

	printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);

	close(sockfd);
	return 0;
}
