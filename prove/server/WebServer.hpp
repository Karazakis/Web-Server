#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
# include "AServer.hpp"

class WebServer : public AServer
{
    private:
        char buffer[30000] = {0};
        int new_socket;
        
        void accepter();
        void handler();
        void responder(); 
    public:
        WebServer();
        void launch();
};

#endif