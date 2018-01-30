#pragma once
#include <curl.h>
#include <string>
class Request
{
public:
	Request(std::string url);
	~Request();
	void send();
	void send(std::string postFields);
	void addHeader(std::string header);
	std::string header;
	std::string body;
private:
	static size_t headerHandler(char* contents, size_t size, size_t nmemb, std::string* str);
	static size_t bodyHandler(char *contents, size_t size, size_t nmemb, std::string* str);
	void setGenericOptions();
	CURL* m_curl;
	std::string m_url;
	struct curl_slist* m_headers = NULL;
};

