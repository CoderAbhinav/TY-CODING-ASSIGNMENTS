// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char hello1[100];
	char* ex = "exit";
	char* hello2 = "Hello from client2\n";
	char* hello3 = "Hello from client3\n";
	char buffer[5000] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	while (hello1[0] != 'e') {
		// scanf("%[^\n]%*c", hello1);
		scanf("%[^\n]%*c",hello1);
		// printf("%s", hello1);
		send(sock, hello1, strlen(hello1), 0);
		valread = read(sock, buffer, 5000);
		printf("%s\n> ", buffer);
	}

	
	
	
	// send(sock, hello2, strlen(hello2), 0);
	// valread = read(sock, buffer, 1024);
	// send(sock, hello3, strlen(hello3), 0);
	// valread = read(sock, buffer, 1024);
	// printf("Hello message sent\n");
	
	

	// closing the connected socket
	close(client_fd);
	return 0;
}

