#include "Responder.hpp"

// Constructor
Responder::Responder(RequestHandler* request, int &socket) : _request(request), _socket(socket) {
    // Initialize or perform any setup required for Responder
}

// Copy Constructor
Responder::Responder(Responder const &src) : _request(src._request), _socket(src._socket) {
    // Implement if needed, otherwise, it can be left empty
}

// Destructor
Responder::~Responder() {
    // Clean up if necessary
}

// Assignment Operator
Responder &Responder::operator=(Responder const &rhs) {
    if (this != &rhs) {
        // Copy the state from rhs to this
        _request = rhs._request;
        _socket = rhs._socket;
    }
    return *this;
}

// Static Method to Send Response Header
void Responder::sendResponseHeader() {
    // Implement the logic to send the response header
    // This might involve using _request and _socket
}

// Static Method to Send Response Body
void Responder::sendResponseBody() {
    // Implement the logic to send the response body
    // This might involve using _request and _socket
}
