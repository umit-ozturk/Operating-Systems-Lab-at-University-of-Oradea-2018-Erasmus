#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h> 		/* for close() */

int main(){
	int server_socket, bytes_recieved, true=1;
	char send_data[1024], recv_data[1024];
	int connected;

	struct sockaddr_in server_address, client_address;
	int sin_size;
	// Create Server Socket
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Socket");
		exit(1);
	}

	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)) == -1){
		perror("Setsockopt");
		exit(1);
	}
	// Define The Server Address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9005);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_address.sin_zero),8);

	// Bind The Server Socket to Our IP and Port
	if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr)) == -1){
		perror("Not Binding");
		exit(1);
	}

	if (listen(server_socket, 5) == -1){
		perror("Not Listening");
		exit(1);
	}

	fflush(stdout);
	
	while(1){
		sin_size = sizeof(struct sockaddr_in);
		connected = accept(server_socket, (struct sockaddr *) &client_address, &sin_size);
		printf("\n Connection from (%s, %d)", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

		while(1){
			printf("\n SEND (q OR Q to quit): ");
			gets(send_data);
			if (strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0){
				// Send Message
				send(connected, send_data, strlen(send_data), 0);
				// Close Socket
				close(connected);
			}
		}
	}	

	return 0;
}