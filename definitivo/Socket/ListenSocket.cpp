#include"ListenSocket.hpp"

ListenSocket::ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bcklg) : BindSocket(domain, service, protocol, port, interface)
{
    backlog = bcklg;
    start_listen();
    test_connection(listening);
    
}

int ListenSocket::getListening()
{
    return listening;
}

void ListenSocket::setListening(int list)
{
    listening = list;
}

void ListenSocket::start_listen()
{
    listening = listen(getSock(), backlog);
}