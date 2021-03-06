#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h> 		/* for close() */


int main(){

	// Create Network Socket
	int network_socket, bytes_recieved;
	char send_data[1024], recv_data[1024];
	struct hostent *host;
	struct sockaddr_in server_address;

	host = gethostbyname("127.0.0.1");

	if ((network_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Socket");
		exit(1);
	}

	// Configration Address for The Socket 
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_address.sin_zero),8);

	// Connection
	if(connect(network_socket, (struct sockaddr *)&server_address,
				 sizeof(struct sockaddr)) == -1){
		perror("Connect");
		exit(1);		
	}

	while(1){
		// receive data from the server
		bytes_recieved = recv(network_socket, recv_data, sizeof(recv_data), 0);
		recv_data[bytes_recieved] = '\0';
		if (strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0){
			close(network_socket);
			break;	
		}
        else{
			printf("\n RECIEVED DATA = %s " , recv_data);
           
			printf("\nSEND (q or Q to quit) : ");
			scanf("%s", send_data);
		}

		if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0)
			send(network_socket,send_data,strlen(send_data), 0); 

		else{
			send(network_socket,send_data, strlen(send_data), 0);   
			close(network_socket);
			break;
		}
	}
	
	return 0;
}