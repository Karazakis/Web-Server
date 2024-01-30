#ifndef RESPONDER_HPP
# define  RESPONDER_HPP
# include "../RequestHandler/RequestHandler.hpp"
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
        void sendResponseHeader();
        void sendResponseBody();

    private:
        int &_socket;
        RequestHandler _request;
};

#endif