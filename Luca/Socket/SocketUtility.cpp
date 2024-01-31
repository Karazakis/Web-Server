#include "SocketUtility.hpp"
#include <fcntl.h> // For fcntl, F_GETFL, F_SETFL, and O_NONBLOCK
#include <cstdio> // For perror

void setSocketNonBlocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0) {
        perror("Error getting flags on socket");
        return;
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Error setting non-blocking flag on socket");
    }
}
