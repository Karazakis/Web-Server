#include "RequestHandler.hpp"
#include "RequestParser.hpp"
#include <sstream>  // For parsing the request
#include <algorithm> // For std::find

RequestHandler::RequestHandler(char *buffer, std::string domain, int port) 
    : _env(), _location_setting(), _type(), _path(), _setting(), _query(), _body(), _body_reponse(), _status(200), is_cgi(false) {
    // Parse the request from buffer and initialize the member variables
    RequestParser parser(buffer); // Use RequestParser to parse the request
    _type = parser.getType();
    _path = parser.getPath();
    // ... Set other member variables based on parser results ...
}

RequestHandler::RequestHandler(RequestHandler const &src) {
    // Implement a copy constructor if needed
}

RequestHandler::~RequestHandler() {
    // Clean up if necessary
}

RequestHandler &RequestHandler::operator=(RequestHandler const &rhs) {
    // Implement assignment operator if needed
    return *this;
}

void RequestHandler::execRequest() {
    // Execute the request based on the parsed data
    // This could involve calling different methods based on _type, etc.
}

bool RequestHandler::isCgi() {
    // Determine if the request should be handled by a CGI script
    return is_cgi;
}

std::string RequestHandler::getResponseHeader() {
    // Generate and return the response header
    std::string responseHeader;
    // Build the response header based on the request and server state
    return responseHeader;
}

std::string RequestHandler::getResponseBody() {
    // Generate and return the response body
    std::string responseBody;
    // Build the response body based on the request and server state
    return responseBody;
}

void RequestHandler::parseRequest(char *buffer) {
    // Implement a method to parse the request
    // This method should set _type, _path, _query, etc., based on the request
    std::istringstream requestStream(buffer);
    // Example: extract the request type (GET, POST, etc.) and the request path
    requestStream >> _type >> _path;
    // Further parsing can be done here as per your requirement
}

// Additional methods for RequestHandler can be added here
