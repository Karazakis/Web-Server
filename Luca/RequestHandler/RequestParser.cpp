#include "RequestParser.hpp"
#include <sstream>  // For parsing the request
#include <string>

RequestParser::RequestParser(char *buffer) : is_cgi(false), _type(), _path(), _setting(), _query(), _body() {
    parseRequest(buffer);
}

RequestParser::RequestParser(RequestParser const &src) {
    // Implement copy constructor if needed
}

RequestParser::~RequestParser() {
    // Clean up if necessary
}

RequestParser &RequestParser::operator=(RequestParser const &rhs) {
    // Implement assignment operator if needed
    return *this;
}

void RequestParser::parseRequest(char *buffer) {
    // Implement a method to parse the request
    // This method should set _type, _path, _query, etc., based on the request
    std::istringstream requestStream(buffer);

    // Example: extract the request type (GET, POST, etc.) and the request path
    requestStream >> _type >> _path;

    // Further parsing can be done here as per your requirement
    // Parse headers, body, query parameters, etc.
}

void RequestParser::takeType() {
    // This method might already be covered in parseRequest
}

void RequestParser::takePath() {
    // This method might already be covered in parseRequest
}

void RequestParser::takeSetting() {
    // Extract and process any specific settings from the request
}

void RequestParser::takeBody() {
    // Extract the body of the request if any
}

void RequestParser::takeQuery() {
    // Extract the query part of the request if any
}

std::string RequestParser::getType() {
    return _type;
}

std::string RequestParser::getPath() {
    return _path;
}

std::string RequestParser::getSetting() {
    return _setting;
}

std::string RequestParser::getQuery() {
    return _query;
}

std::string RequestParser::getBody() {
    return _body;
}
