#include "AServer.hpp"

AServer::AServer(int domain, int service, int protocol, int port, u_long interface, int bcklg)
{
    socket = new ListenSocket(domain, service, protocol, port, interface, bcklg);
    std::cout << "nel server" << socket->getListening() << std::endl;
}

ListenSocket *AServer::getSocket()
{
    return socket;
}