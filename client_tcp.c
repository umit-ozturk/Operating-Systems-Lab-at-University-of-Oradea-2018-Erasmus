#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 		/* for close() */


int main(){

	// Create Network Socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Configration Address for The Socket 
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	// Connection
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	printf("%d\n", connection_status);

	if (connection_status == -1){
		printf("Something went wrong \n\n");
	}


	// receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	printf("Receive from server --> %s\n", server_response);

	close(network_socket);
	
	return 0;
}