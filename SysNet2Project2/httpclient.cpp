/* File Name:	httpclient.cpp
 * Course:	COP4635
 * Project:	2
 * Author:	Jeremy Caole Kevin Teague
 * Description:	httpclient connects to remote server over TCP/IP, sends GET requests to 
 * 		retreive user specified files.
 */


#include "httpclient.hpp"

void runHttpClient();

char SERVER_ADDRESS[MAX_BUFF_SIZE];

/*
 * ask for user input for server address, 127.0.0.1
 */
void setServerAddress() {
	printf("Please enter the server address: ");
	scanf("%s", SERVER_ADDRESS);
}

char REQUEST_TEMPLATE[MAX_BUFF_SIZE] =
	"GET /%s HTTP/1.1\r\n"
	"Host: %s\r\n"
	"Connection: close\r\n"
	"\r\n";

/*
 * main method to run client and prompt user for file name and server address
 */
int main() {
	setServerAddress();
	while (1) {
		runHttpClient();
	}
	return 0;
}

/*
 * core method 
 */
void runHttpClient() {
	char filename[MAX_BUFF_SIZE];
	char request[MAX_BUFF_SIZE];
	char server_response[MAX_BUFF_SIZE];
	struct sockaddr_in server_address;
	int client_socket;

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

	// formulate the request to be sent to the server
	sprintf(request, REQUEST_TEMPLATE, filename, SERVER_ADDRESS);

	printf("Sending request to the server:\n%s", request);

	/*
	 * send the request to the server
	 */
	if (send(client_socket, request, strlen(request), 0) < 0) {
		perror("Error: Failed to send the request to the server");
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
	printf("Received data from the server:\n%s", server_response);

	/* close socket and clear all memory
	 *
	 */
	close(client_socket);
	memset(server_response, 0, MAX_BUFF_SIZE);
	memset(request, 0, MAX_BUFF_SIZE);
}
