/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */

#include "httpclient.hpp"

/*
 * main method to run client and prompt user for file name and server port & address
 */


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
    if ((he = gethostbyname(hostname)) == NULL) {
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
    printf("Enter filename: ");
    scanf("%s", filename);

    // resolve hostname and connect to server
    resolve_and_connect(hostname, filename);

    return 0;
}

