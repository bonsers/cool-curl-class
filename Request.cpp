#include "Request.h"
#include <iostream>


Request::Request(std::string url) : m_url(url)
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl = curl_easy_init();
}


Request::~Request()
{
	curl_easy_cleanup(m_curl);
}


size_t Request::headerHandler(char* contents, size_t size, size_t nmemb, std::string* str)
{
	str->append(contents);
	return size * nmemb;
}


size_t Request::bodyHandler(char *contents, size_t size, size_t nmemb, std::string* str)
{
	str->append(contents);
	return size * nmemb;
}


void Request::send()
{
	if (m_curl)
	{
		setGenericOptions();
		//curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1L);

		CURLcode res = curl_easy_perform(m_curl);
		if (res != CURLE_OK)
		{
			//std::cout << res << " " << curl_easy_strerror(res) << std::endl;
			throw std::runtime_error(curl_easy_strerror(res));
		}
	}
}



void Request::send(std::string postFields)
{
	if (m_curl)
	{
		setGenericOptions();
		
		curl_easy_setopt(m_curl, CURLOPT_POST, 1L);
		curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
		curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, postFields.c_str());
		
		CURLcode res = curl_easy_perform(m_curl);
		if (res != CURLE_OK)
		{
			throw std::runtime_error(curl_easy_strerror(res));
		}
	}
}


void Request::setGenericOptions()
{
	curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_curl, CURLOPT_HEADERFUNCTION, headerHandler);
	curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &header);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, bodyHandler);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &body);
}


void Request::addHeader(std::string header)
{
	m_headers = curl_slist_append(m_headers, header.c_str());
}