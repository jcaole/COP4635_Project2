/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */


#include "httpclient.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFF_SIZE 1024
#define SERVER_PORT 80

void run_http_client();

char SERVER_ADDRESS[MAX_BUFF_SIZE];

void set_server_address() {
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
	set_server_address();
	while (1) {
		run_http_client();
	}
	return 0;
}

void run_http_client() {
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




/*
 * main method to run client and prompt user for file name and server port & address
 */

/* 
 * bool is_valid_ip_address(const char* ip_address) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip_address, &(sa.sin_addr)) != 0;
}

void resolve_and_connect(char *hostname, char *filename) {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // resolve hostname
    struct hostent *he;
    if (is_valid_ip_address(hostname)) {
        struct in_addr ip_addr;
        inet_pton(AF_INET, hostname, &ip_addr);
        he = gethostbyaddr(&ip_addr, sizeof(ip_addr), AF_INET);
    } else {
        he = gethostbyname(hostname);
    }

    if (he == NULL) {
        perror("Failed to resolve hostname");
        exit(EXIT_FAILURE);
    }

    // set server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr = *((struct in_addr *) he->h_addr);

    // connect to server
    if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    // send HTTP request
    sprintf(buffer, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", filename, hostname);
    if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
        perror("Failed to send request");
        exit(EXIT_FAILURE);
    }

    // receive HTTP response
    int num_bytes;
    while ((num_bytes = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[num_bytes] = '\0';
        printf("%s", buffer);
    }

    // close socket
    close(client_socket);
}


int main(int argc, char *argv[]) {
    char hostname[BUFFER_SIZE];
    char filename[BUFFER_SIZE];

    // get hostname and filename from user
    printf("Enter hostname: ");
    scanf("%s", hostname);

    // prompt user to input a valid hostname or IP address
    while (!is_valid_ip_address(hostname) && gethostbyname(hostname) == NULL) {
        printf("Invalid hostname, please enter a valid hostname or IP address: ");
        scanf("%s", hostname);
    }

    printf("Enter filename: ");
    scanf("%s", filename);

    // resolve hostname and connect to server
    resolve_and_connect(hostname, filename);

    return 0;
}
*/

