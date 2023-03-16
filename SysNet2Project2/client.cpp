/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */

#include "client.hpp"

/*
 * main method to run client and prompt user for file name and server port & address
 */
int main() {
run_tcp_client();
return 0;
}
void run_tcp_client() {
	int client_socket;
    	char server_response[MAX_BUFF_SIZE], filename[MAX_BUFF_SIZE], message[MAX_BUFF_SIZE];
    	struct sockaddr_in server_address;

    	/*
	 * create the TCP client socket
	 */
    	client_socket = socket(AF_INET, SOCK_STREAM, 0);
    	if (client_socket < 0) {
		perror("Error: Failed to create the client socket");
		exit(EXIT_FAILURE);
    	}

    	/*
	 * specify the address and port of the remote server socket
	 */
    	memset(&server_address, 0, sizeof(server_address));
    	server_address.sin_family = AF_INET;


    	/*
    	 * approach, create setter handler to request for server port and address.
	*/
    	server_address.sin_port = htons(SERVER_PORT);
    	server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    	/*
	 * connect to the remote socket
	 */
    	if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
		perror("Error: Failed to connect to the server");
		close(client_socket);
		exit(EXIT_FAILURE);
    	}
    	printf("Successfully connected to the server.\n");

    	/*
	 * prompt for file name and read it
	 */
    	printf("Please enter the file name: ");
    	scanf("%s", filename);


    	// formulate the message to be sent to the server
    	memset(message, 0, MAX_BUFF_SIZE);
    	strcat(message, "GET ");
    	strcat(message, filename);
    	strcat(message, "\r\n");


    	printf("Sending message to the server: %s", message);


    	/*
	 * send the message to the server
	 */
    	if (send(client_socket, message, strlen(message), 0) < 0) {

		perror("Error: Failed to send the message to the server");

		close(client_socket);

		exit(EXIT_FAILURE);

    	}

    	/* receive data from server and display it on the client
	 *
	 */
    	memset(server_response, 0, MAX_BUFF_SIZE);
    	if (recv(client_socket, server_response, MAX_BUFF_SIZE, 0) < 0) {
		perror("Error: Failed to receive data from the server");
		close(client_socket);
		exit(EXIT_FAILURE);
    	}
    	printf("Received data from the server: %s", server_response);

    	/* close socket and clear all memory
	 *
	 */
    	close(client_socket);
    	memset(server_response, 0, MAX_BUFF_SIZE);
    	memset(filename, 0, MAX_BUFF_SIZE);
    	memset(message, 0, MAX_BUFF_SIZE);
}
