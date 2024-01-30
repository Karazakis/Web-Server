#include "Server.hpp"

// Constructor
Server::Server(std::multimap<std::string, std::string> env) : _env(env) {
    // Initialize any necessary members
    // For example, setting up socket_container based on _env settings
    // ...
}

// Copy Constructor
Server::Server(Server const &src) {
    // Implement a deep copy if necessary
    *this = src;
}

// Destructor
Server::~Server() {
    // Clean up resources if any
    // ...
}

// Assignment Operator
Server &Server::operator=(Server const &rhs) {
    if (this != &rhs) {
        // Copy all the member variables from rhs to this
        _env = rhs._env;
        _location_setting = rhs._location_setting;
        _request = rhs._request;
        _response_header = rhs._response_header;
        // You may need to handle socket_container separately if it cannot be copied directly
    }
    return *this;
}

// takeLocation Function
void Server::takeLocation() {
    // Implement logic to process location settings
    // This might involve parsing _env to configure _location_setting
    // For example:
    for (const auto &pair : _env) {
        if (pair.first == "location") {
            // Assuming 'location' key in _env needs special handling
            // Modify or add to _location_setting based on the value of pair.second
            // ...
        }
    }
}

void Server::run(char *buffer, int &socket, std::string domain, int port)
{
    takeLocation();
    RequestHandler request(buffer, domain, port);
    // Optionally set _env and _location_setting via other methods if needed
    // request.setEnv(_env);
    // request.setLocationSetting(_location_setting);
    Responder(request, socket);
}

void Server::closeServer() {
    // Close all socket connections and clean up resources
    for (auto& socket : socket_container) {
        // Assuming socket_container holds instances of ListenSocket or similar
        // You need to call a method to properly close each socket
        socket.closeSocket();  // Implement closeSocket() in your socket class
    }   
    // Additional cleanup if necessary
    // For example, if you have dynamically allocated memory or other resources
    // associated with the Server instance, make sure to release them here
}