/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */


#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFF_SIZE 1024
#define SERVER_PORT 80

void run_http_client();

void set_server_address();

#endif

/*#include <iostream>
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
		bool is_valid_ip_address(const char* ip_address);
		void resolve_and_connect(char *hostname, char *filename);
};
#endif
*/
