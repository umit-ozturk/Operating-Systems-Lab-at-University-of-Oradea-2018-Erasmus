#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 		/* for close() */

int main(){
	char server_message[256] = "You have received the server";

	// Create Server Socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Define The Server Address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind The Server Socket to Our IP and Port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	client_socket = accept(client_socket, NULL, NULL);

	// Send Message
	send(client_socket, server_message, sizeof(server_message), 0);

	// Close Socket
	
	close(server_socket);

	return 0;
}