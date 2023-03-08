#ifndef ACTIONHANDLER_HPP
#define ACTIONHANDLER_HPP

/* File Name:	actionhandler.hpp
 * Date Edited:	02/03/23
 * Course:	COP4635
 * Project:	#1
 * Author:	Jeremy Caole, Kevin Teague
 * Description: Header file for actionhandler class.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>

class ActionHandler {
	
	/*
	 * c struct for requests
	 */
	struct request {
		std::string method;
		std::string uri;
		std::string protocolVector;
	};

	/*
	 * c struct for response
	 */
	struct response {
		std::string protocolVector;
		
		std::string message;
		std::string body;
		std::string status;

		int length;
	};

	private:
	struct request ask;
	struct response answer;			
	std::vector <std::string> body;		//content of html page
	std::string responseToClient;		//used in server method

	//parse characters method
	void parse(char *buffer);

	//read file from location
	void readFile(std::string loc);
	
	//setters
	void setRequest();
	void setResponse();

	void setStatus();

	void setHTML();
	void setPicture();
	void setErrorHandler();

	public:
	/*
	 * param constructor used to be called in main
	 */
	ActionHandler(char *buffer);
	
	/*
	 * getters
	 */
	std::string getResponseToClient();
};
#endif	/*ACTIONHANDLER_HPP*/
