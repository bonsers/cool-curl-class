#include <iostream>
#include "request.h"

int main()
{
	// SEND GET
	//Request req("http://www.learncpp.com/");
	//req.send();

	// SEND POST (default content type: x-www-form-urlencoded)
	Request req("http://httpbin.org/post");
	req.send("p=hello&q=world");

	// SEND JSON POST
	/*Request req("http://httpbin.org/post");
	req.addHeader("Accept: application/json");
	req.addHeader("Content-Type: application/json");
	req.addHeader("charsets: utf-8");
	req.send("{\"username\":\"xyz\",\"password\":\"xyz\"}");*/

	std::cout << req.header << std::endl;
	std::cout << req.body << std::endl;
}