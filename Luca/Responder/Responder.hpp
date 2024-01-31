#ifndef RESPONDER_HPP
#define RESPONDER_HPP
#include "../WebServer.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

class RequestHandler;

class Responder {
public:
    Responder(RequestHandler* request, int &socket);
    Responder(const Responder &src);
    ~Responder();

    Responder &operator=(const Responder &rhs);

    void sendResponseHeader();
    void sendResponseBody();

private:
    int &_socket;
    RequestHandler* _request;
};

#endif // RESPONDER_HPP
