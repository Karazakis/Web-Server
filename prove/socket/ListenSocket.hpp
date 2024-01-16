#ifndef LISTENSOCKET_HPP
# define LISTENSOCKET_HPP
# include "BindSocket.hpp"

class ListenSocket : public BindSocket
{
    private:
        int backlog;
        int listening;
    public:
        ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bcklg);
        void start_listen();
        int getListening();
        void setListening(int list);
};

#endif