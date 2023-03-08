/* File Name:	httpserver.cpp
 * Date Edited:	02/03/23
 * Course:	COP4635
 * Project:	#1
 * Author:	Jeremy Caole, Kevin Teague
 * Description:	tcpserver sets up server that will listen for client requests
 */

#include "httpserver.hpp"

HTTPServer::HTTPServer() {}

/*
 * start method starts server connection
 */
void HTTPServer::start() {
	std::cout << "Server started." << std::endl;
	if((tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR: listening socket failed | start() if statement");
		exit(1);
	}

	/*
	 * variables given in server template
	 */
	tcp_server_address.sin_family = AF_INET;
	tcp_server_address.sin_addr.s_addr = INADDR_ANY;
	tcp_server_address.sin_port = htons(PORT);

	/*
	 * use of bind method
	 */
	memset(tcp_server_address.sin_zero, '\0', sizeof tcp_server_address.sin_zero);
//	std::cout << "binding" << std::endl;
	printf("Bind:\n");
	if(bind(tcp_server_socket, (struct sockaddr *) &tcp_server_address, sizeof(tcp_server_address)) < 0) {
//		std::cout << "testing: binding failed, reached first if statement" << endl;
		perror("ERROR: Binding failed | if statement in start method, HTTPServer class");
		exit(1);
	}

	/*
	 * use of listen method
	 */
	std::cout << "Server listening..." << std::endl;
	if(listen(tcp_server_socket, waitSize) < 0) {
//		std::cout << "testing failed to listen" << std::endl;
		perror("ERROR: failed to listen | if statement (listen(server_fd, waitSize) < 0)");
		exit(1);
	}
//	std::cout << "testing: was able to listen" << std::endl;
	std::cout << "Server waiting for client request..." << std::endl;
}

/*
 * run method
 */
void HTTPServer::run() {
	while(1) { //loop does not end to keep server running
		/*
		 * use of accept method, given code from server template
		 */
		if((client_socket = accept(tcp_server_socket, (struct sockaddr *) &tcp_server_address, (socklen_t *) & addressLength)) < 0) {
			perror("ERROR: server failed to accept client | run method in HTTPServer class");
			exit(1);
		}
		/*
		 * fork method used for client
		 */
		if(fork() == 0 ) {
//			std::cout << "testing fork" << std::endl;
			std::cout << "Client connected." << std::endl;

			char buffer[3000];
			/*
			 * use of read function
			 */
			while((valueToRead = read(client_socket, buffer, 30000)) > 0 ) {
				ActionHandler h(buffer);
				std::string message = h.getResponseToClient();
				
				/*
				 * use of write function
				 */
				write(client_socket, (char *) message.c_str(), (int) message.size());
			}
			/*
			 * close client socket after completed task
			 */
			close(client_socket);
			exit(0);
		}
		else {
//			std::cout << "testing" << std::endl;
			std::cout << "listening and waiting for more clients." << std::endl;
		}
	}
}
