#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if(argc < 2 && argc > 2)
	{
		printf("Invalid arguments\n");
		printf("Usage: ./web_client <address>\n");
		printf("\n");
		return -1;
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Error creating socket\n"); 
		return -1;
	}

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(80);
	if(inet_pton(AF_INET, argv[1], &(address.sin_addr)) < 1)
	{
		printf("Invalid IP Address\n");
		return -1;
	}
	
	if(connect(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
	{
		printf("Connection failed\n");
		return -1;
	}
	
	const char *request = "GET / HTTP/1.1\r\n\r\n";
	
	write(sockfd, request, strlen(request));
	char buffer[1024];

	while(read(sockfd, buffer, sizeof(buffer) - 1) > 0)
	{
		printf("%s", buffer);
	}
	
	close(sockfd);
	
	return 0;
}
