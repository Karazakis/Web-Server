#include"BindSocket.hpp"

BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface) : ASocket(domain, service, protocol, port, interface)
{
    connect_to_network(getSock(), getAddr());
    test_connection(binding);
    std::cout << "nel bind" << std::endl;
}

void BindSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    binding = bind(sock, (struct sockaddr *)&address, sizeof(address));
}

