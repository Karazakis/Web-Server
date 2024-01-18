#include"ASocket.hpp"

ASocket::ASocket(int domain, int service, int protocol, int port, u_long interface)
{
    //definisci struttura indirizzo
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    //creazione socket
    sock = socket(domain, service, protocol);
    test_connection(sock);
    std::cout << "nel sock" << std::endl;
}

void ASocket::test_connection(int item_to_test)
{
    if (item_to_test < 0)
    {
        perror("Fail...");
        exit(1);
    }
}

struct sockaddr_in ASocket::getAddr() {
    return(address);
}

int ASocket::getSock() {
    return(sock);
}

void ASocket::setAddr(struct sockaddr_in addr) {
    address = addr;
}

void ASocket::setSock(int soc)
{
    sock = soc;
}
