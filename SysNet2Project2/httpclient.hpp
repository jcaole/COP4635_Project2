/* File Name:	httpclient.hpp
 * Course:	COP4635
 * Project:	2
 * Author:	Jeremy Caole Kevin Teague
 * Description:	Header file for httpclient class
 */

#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// used to convert ip address data to byte order
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFF_SIZE 1024
// port 80 doesnt work
#define SERVER_PORT 60012

void runHttpClient();		// runs client with for specidifed user params

void setServerAddress();	

int main();			// main method for httpclient

#endif /* HTTP_CLIENT_H_ */
