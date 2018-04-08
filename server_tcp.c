#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	char server_messg[256] = "You have received the server";

	// Create Server Socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Define The Server Address
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9002);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	return 0;
}