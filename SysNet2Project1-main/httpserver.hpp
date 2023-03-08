/* File Name: httpserver.hpp
 * Date Edited:	02/03/23
 * Course: COP4635
 * Project: #1
 * Author: Jeremy Caole, Kevin Teague
 * Description: Header file for http server class.
 */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include "actionhandler.hpp"

#define PORT 60012

class HTTPServer {
	private:
		int tcp_server_socket;					//given variable from server template
		int client_socket;					//given variable from server template
		long valueToRead;					//variable used for parsed string
		int waitSize = 16;					//
		struct sockaddr_in tcp_server_address;			//given variable from server template
		int addressLength = sizeof(tcp_server_address);

	public:
		HTTPServer();						//default constructor
		void start();						//starts server and listens for actions
		void run();						//starts server
};
#endif /*HTTPSERVER_HPP*/
