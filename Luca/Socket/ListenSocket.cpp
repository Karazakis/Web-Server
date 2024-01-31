#include"ListenSocket.hpp"

ListenSocket::ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bcklg) : BindSocket(domain, service, protocol, port, interface)
{
    backlog = bcklg;
    setSocketNonBlocking(getSock());

    listening = listen(getSock(), backlog);
    if (listening < 0) {
        perror("ListenSocket: Error in starting listen");
        // Handle error appropriately
    }
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