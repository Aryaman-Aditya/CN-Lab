#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

long long factorial(int n){ //function for factorial calculation
	long long fact = 1;
	for (int i = 1; i <= n; i++) {
		fact *= i;
	}
	return fact;
}

int main(){
	int sockfd;
	int b1;
	struct sockaddr_in server, client;

	int socket(int domain, int type, int protocol);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0) {
		printf("Error in socket creation\n");
	}
	else{
		printf("Socket created successfully\n");
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = INADDR_ANY;

	b1 = bind(sockfd, (struct sockaddr*)&server, sizeof(server));

	if (b1 < 0) {
		printf("Error in binding\n");
	}
	else{
		printf("Binding successful\n");
	}

	printf("\nPort no: %d\n IP address: %s\n", ntohs(server.sin_port), inet_ntoa(server.sin_addr));

	char buffer[1024];
	socklen_t len = sizeof(client);
	ssize_t rec_size;
	rec_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &len);

	printf("Data received of size %ld \n data is: %s\n", rec_size, buffer);

	int n = atoi(buffer);
	long long result = factorial(n);

	char result_buffer[1024];
	sprintf(result_buffer, "%lld", result);

	ssize_t send_size;
	send_size = sendto(sockfd, result_buffer, strlen(result_buffer)+1, 0, (struct sockaddr *)&client, len);

	close(sockfd);

	return 0;
}
