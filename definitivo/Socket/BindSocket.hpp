#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP
# include "ASocket.hpp"

class BindSocket : public ASocket
{
    private:
        int binding;
        void connect_to_network(int sock, struct sockaddr_in address);
    public:
        BindSocket(int domain, int service, int protocol, int port, u_long interface);
        int getBinding();
};

#endif