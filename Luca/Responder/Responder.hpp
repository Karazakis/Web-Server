#ifndef RESPONDER_HPP
# define  RESPONDER_HPP
# include "../WebServer.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class Responder
{
    public:
        Responder(Responder const &src);
        ~Responder();
        Responder(RequestHandler request, int &socket);
        
        Responder &operator=(Responder const &rhs);
        static void sendResponseHeader();
        static void sendResponseBody();

    private:
        static int &_socket;
        static RequestHandler _request;
};

#endif