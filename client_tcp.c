#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){

	// Create Network Socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Configration Address for The Socket 
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9002);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Connection
	int con_status = connect(network_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));

	if (con_status == -1){
		printf("Something went wrong");
	}

	return 0;
}