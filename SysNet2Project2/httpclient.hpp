/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <iostream>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define PORT 80

//#define SERVER_ADDRESS

class HTTPClient {
	private:
		
	public:
		void resolve_and_connect(char *hostname, char *filename);
};
#endif
