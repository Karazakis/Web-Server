#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

struct SocketInfo {
    int socket;
    bool isServer;
    int port;  // Aggiunto il numero di porta
    std::string domain;  // Aggiunto il dominio
};

int main() {
    const int SERVER_PORT_1 = 12345;
    const int SERVER_PORT_2 = 54321;

    // Creazione del socket del server 1
    int serverSocket1 = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket1 == -1) {
        perror("Errore nella creazione del socket del server 1");
        return 1;
    }

    // Impostazione dell'indirizzo del server 1
    struct sockaddr_in serverAddr1;
    serverAddr1.sin_family = AF_INET;
    serverAddr1.sin_port = htons(SERVER_PORT_1);
    serverAddr1.sin_addr.s_addr = INADDR_ANY;

    // Associazione dell'indirizzo al socket
    if (bind(serverSocket1, (struct sockaddr *)&serverAddr1, sizeof(serverAddr1)) == -1) {
        perror("Errore nella bind del server 1");
        close(serverSocket1);
        return 1;
    }

    // ... Ripeti il processo per il server 2 ...

    std::vector<SocketInfo> sockets;
    sockets.push_back(SocketInfo(serverSocket1, true, SERVER_PORT_1, "domain1"));
    // Aggiungi anche le informazioni per serverSocket2

    // ... Continua con il codice ...

    while (true) {
        fd_set readSet;
        FD_ZERO(&readSet);

        int maxfd = 0;

        for (std::vector<SocketInfo>::iterator it = sockets.begin(); it != sockets.end(); ++it) {
            FD_SET(it->socket, &readSet);
            maxfd = std::max(maxfd, it->socket);
        }

        int selectResult = select(maxfd + 1, &readSet, NULL, NULL, NULL);

        if (selectResult == -1) {
            perror("Errore nella select");
            break;
        }

        for (std::vector<SocketInfo>::iterator it = sockets.begin(); it != sockets.end(); ++it) {
            const SocketInfo &socketInfo = *it;

            if (FD_ISSET(socketInfo.socket, &readSet)) {
                if (socketInfo.isServer) {
                    // Nuova connessione in ingresso
                    int newClientSocket = accept(socketInfo.socket, NULL, NULL);
                    if (newClientSocket == -1) {
                        perror("Errore nell'accettare la connessione");
                    } else {
                        std::cout << "Nuova connessione accettata su porta " << socketInfo.port << " e dominio " << socketInfo.domain << std::endl;
                        sockets.push_back(SocketInfo(newClientSocket, false, socketInfo.port, socketInfo.domain));
                    }
                } else {
                    // Dati da un client esistente
                    char buffer[1024];
                    int bytesRead = recv(socketInfo.socket, buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0) {
                        close(socketInfo.socket);
                        it = sockets.erase(it);
                        std::cout << "Socket disconnesso" << std::endl;
                    } else {
                        buffer[bytesRead] = '\0';
                        std::cout << "Messaggio dal socket su porta " << socketInfo.port << " e dominio " << socketInfo.domain << ": " << buffer << std::endl;
                    }
                }
            }
        }
    }

    // ... Continua con la chiusura dei socket ...

    return 0;
}
