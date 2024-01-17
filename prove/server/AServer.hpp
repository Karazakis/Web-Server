#ifndef ASERVER_HPP
# define ASERVER_HPP
# include "../socket/LibSocket.hpp"

class AServer
{
    protected:
        ListenSocket *socket;
        virtual void accepter() = 0;
        virtual void handler() = 0;
        virtual void responder() = 0; 
    public:
        AServer(int domain, int service, int protocol, int port, u_long interface, int bcklg);
        virtual void launch() = 0;
        ListenSocket *getSocket();
};

#endif