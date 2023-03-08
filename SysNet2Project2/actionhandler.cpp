/* File Name:	actionhandler.cpp
 * Date Edited:	02/03/23
 * Course:	COP4635
 * Project:	#1
 * Author:	Jeremy Caole
 * Description: actionhandler class handles client requests and server responses.
 */

#include "actionhandler.hpp"

/*
 * param constructor
 */
ActionHandler::ActionHandler(char *buffer) {
	responseToClient = "";
	parse(buffer);
}

/*
 * parse method
 */
void ActionHandler::parse(char *buffer) {
	std::string str;
	std::stringstream ss(buffer);

	while(ss >> str) {
		body.push_back(str);
	}
	setResponse();
}

/*
 * setters
 */

/*
 * method sets response
 */
void ActionHandler::setResponse() {
	int i = 0;

	ask.method = body.at(i++);
	ask.uri = body.at(i++);
	ask.protocolVector = body.at(i);

	setRequest();
}

/*
 * method sets request, utilizes status method for status codes
 */
void ActionHandler::setRequest() {
	answer.protocolVector = ask.protocolVector;

	setStatus();
}

/*
 * method that sets the HTTP status code: 200"success status - OK" 404"client error - NOT FOUND"
 */
void ActionHandler::setStatus() {
	if(ask.uri == "/") {
		answer.status = "200";
		answer.message = "OK";

		ask.uri = "/index.html";

		readFile(ask.uri);
		setHTML();
		return;
	}
	else if(ask.uri == "/testPresence.html") {
		answer.status = "200";
		answer.message = "OK";

		readFile(ask.uri);
		setHTML();
		return;
	}
	else if(ask.uri.compare("/img.jpg") == 0) {
		answer.status = "200";
		answer.message = "OK";

		readFile(ask.uri);
		setPicture();
		return;
	}

//	testing given html.
/*	else if(ask.uri.compare("/fake.html") == 0) {
		answer.status = "404";
		answer.message = "Not Found\n";
		setErrorHandler();
		return;
	}
*/
	else {
		answer.status = "404";
		answer.message = "Not Found\n";
		setErrorHandler();
		return;
	}
}

/*
 * method that sets picture
 */
void ActionHandler::setPicture() {
	std::stringstream ss;

	ss << answer.protocolVector << " " << answer.status << " " << answer.message << "\n";
	ss << "Content-Type: img.jpg\n";
	ss << "Content-Length: ";
	ss << answer.length;
	ss << "\n\n";
	ss << answer.body;

	responseToClient = ss.str();

	std::cout << "picture was sent" << std::endl;
}

/*
 * method that sets html for client
 */
void ActionHandler::setHTML() {
	std::stringstream ss;
	ss << answer.protocolVector << " " << answer.status << " " << answer.message << "\n";
	ss << "Content-Type: img.jpg\n";
        ss << "Content-Length: ";
        ss << answer.length;
        ss << "\n\n";
	ss << answer.body;

	responseToClient = ss.str();

	std::cout << ask.uri << "file was sent" << std::endl;
}

/*
 * method that sets the error message to client
 */
void ActionHandler::setErrorHandler() {
	responseToClient = "HTTP/1.1 404 Not Found\n"		//error code 404
	       		   "Content-Type: text/plain\r\n"	//plain text
			   "Content-Length: 15\n\n\r\n"		//note: length set to 15 to fully display plain text: 404 Not Found
			   "404 Not Found\r\n";
	//server output
	std::cout << "error message was sent | ERRORCODE: 404" << std::endl;
}

/*
 * read body for asked file to be displayed in web browser
 */
void ActionHandler::readFile(std::string loc) {
	//erase(): delete the specific character at the specified iterator position
	loc = loc.erase(0,1);
	//use of binary
	std::ifstream input(loc, std::ifstream::binary);
	if(input) {
		std::stringstream ss;
		ss << input.rdbuf();
		std::string s = ss.str();
		input.close();
		answer.length = (int) s.size();
		answer.body = s;
	}
}

// getter for responseToClient, used in server method
std::string ActionHandler::getResponseToClient() {
	return responseToClient;
}
