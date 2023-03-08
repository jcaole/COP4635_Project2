/* File Name:
 * Course:
 * Project:
 * Author:
 * Description:
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 60012

#define MAX_BUFF_SIZE 1024

void run_tcp_client();

#endif
