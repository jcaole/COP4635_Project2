/* File Name: 	main.cpp
 * Date Edited:	02/03/23
 * Course:	COP4635
 * Project:	#1
 * Author:	Jeremy Caole, Kevin Teague
 * Description:	main file
 */

#include "httpserver.hpp"

int main() {
	HTTPServer server;
	server.start();
	server.run();
}
