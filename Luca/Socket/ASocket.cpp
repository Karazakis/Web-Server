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
        exit(EXIT_FAILURE);
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

void ASocket::closeSocket() {
    if (sock != -1) {
        // Close the socket
        close(sock);
        sock = -1;  // Reset the socket descriptor to an invalid value
    }

    // Perform additional cleanup if necessary
}

// void ASocket::setSocketNonBlocking2() {
//     int flags = fcntl(sock, F_GETFL, 0);
//     if (flags == -1) {
//         perror("setSocketNonBlocking: Error getting flags");
//         // Handle error appropriately
//     }

//     flags |= O_NONBLOCK;
//     if (fcntl(sock, F_SETFL, flags) == -1) {
//         perror("setSocketNonBlocking: Error setting non-blocking");
//         // Handle error appropriately
//     }
// }

