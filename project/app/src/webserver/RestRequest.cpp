/*
 * RestRequest.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <RestRequest.h>

RestRequest::RestRequest(http_message * hm) {
	this->message = hm;
	this->uri = extractUri(hm);
    std::string data (*(&hm->body.p));
    this->content = data;
}

RestRequest::~RestRequest() {
	// TODO Auto-generated destructor stub
}

string RestRequest::getUri() {
	return uri;
}

string parseMethod(	http_message * message) {
	std::string method (*(&message->method.p));
	 std::size_t found = method.find(" ");
	 if (found!=std::string::npos)
	    method = method.substr(0,found);
	 return method;
}

string RestRequest::extractUri(http_message* hm) {
	  string uri (*(&hm->uri.p));
	  std::size_t found = uri.find(" ");
	   if (found!=std::string::npos)
	     uri = uri.substr(0,found);
	   return uri;
}

string RestRequest::toString() {
	 string method = parseMethod(this->message);

	return method + ": " + this->getUri();
}

RestRequest::Method RestRequest::getMethod() {
	string method = parseMethod(this->message);
	if( method == "GET") return GET;
	if( method == "PUT") return PUT;
	if( method == "POST") return POST;
	if( method == "DELETE") return DELETE;
	return UNKNOWN;

}

string RestRequest::getDescription(RestRequest::Method method) {
	switch (method) {
		case PUT:
			return "PUT";
			break;
		case POST:
			return "POST";
			break;
		case GET:
			return "GET";
			break;
		case DELETE:
			return "DELETE";
			break;
		default:
			break;
	}
	return "";

}
