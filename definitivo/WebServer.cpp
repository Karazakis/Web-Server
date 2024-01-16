#include "WebServer.hpp"

SocketInfo::SocketInfo(int por, std::vector< std::string > allowed_doman)
{
    socket_class = new ListenSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10);
    socket = &socket_class->getSock();
    port = por;
    allowed_domain = allowed_doman;
}

SocketInfo::SocketInfo(int &sock, int por, std::string doman, std::vector< std::string > allowed_doman) : port(por), socket(sock), allowed_domain(allowed_doman)
{

}

WebServer::WebServer(char *filename)
{
    std::multimap<std::string, std::string> defaul_env = loadDefaultEnv();
    Config config(filename, defaul_env);
    _env = config.getEnv();
    for(int i = 0; i < _env.size(); i++)
    {
        Server *tmp = new Server(_env[i]);
        for(int j = 0; j < _env[i]["server_name"].size(); j++)
            _server.insert(std::pair<std::string, Server & >((_env[i])["server_name"], tmp));
        for (std::multimap<std::string, std::string>::iterator it = _env[i].begin(); it != _env[i].end(); ++it) 
            if (it->first == "port") 
                if (/*se il socket sulla porta esiste già*/)
                    _socket.push_back(SocketInfo(it->second, _env[i]));
    }
}

void WebServer::run()
{
    sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);
    char clientDomain[NI_MAXHOST];
    int domainResult;

    while (true) {
        fd_set readSet;
        FD_ZERO(&readSet);

        int maxfd = 0;

        for (std::vector<SocketInfo>::iterator it = _socket.begin(); it != _socket.end(); ++it) {
            FD_SET(it->socket, &readSet);
            maxfd = std::max(maxfd, it->socket);
        }

        int selectResult = select(maxfd + 1, &readSet, NULL, NULL, NULL);

        if (selectResult == -1) {
            perror("Errore nella select");
            break;
        }

        for (std::vector<SocketInfo>::iterator it = _socket.begin(); it != _socket.end(); ++it) {
            const SocketInfo &socketInfo = *it;

            if (FD_ISSET(socketInfo.socket, &readSet)) {
                //quando ha trovato il socket che ha roba da dire
                if (socketInfo.isServer) {
                    // Nuova connessione in ingresso da rifare, connessione gestita da singolo server e poi socket aggiunto a lista generale
                    int newClientSocket = accept(socketInfo.socket, NULL, NULL);
                    if (newClientSocket == -1) {
                        perror("Errore nell'accettare la connessione");
                    } else {
                        domainResult = getpeername(newClientSocket, (struct sockaddr*)&addr, &addrLen);
                        if (domainResult == 0) {
                            domainResult = getnameinfo((struct sockaddr*)&addr, addrLen, clientDomain, sizeof(clientDomain), NULL, 0, NI_NAMEREQD);
                            if (domainResult == 0) {
                                if (!isAllowedDomain(clientDomain, socketInfo.allowed_domain)) {
                                    std::cerr << "Connessione rifiutata da " << clientDomain << std::endl;
                                    close(newClientSocket);
                                } else {
                                    std::cout << "Nuova connessione accettata su porta " << socketInfo.port << " e dominio " << clientDomain << std::endl;
                                    _socket.push_back(SocketInfo(newClientSocket, false, socketInfo.port, clientDomain));
                                }
                            } else {
                                perror("Errore nella risoluzione del dominio");
                                close(newClientSocket);
                            }
                        } else {
                            perror("Errore nel recupero dell'indirizzo del peer");
                            close(newClientSocket);
                        }
                    }
                } else {
                    // Dati da un client esistente
                    char buffer[1024];
                    int bytesRead = recv(socketInfo.socket, buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0) {
                        close(socketInfo.socket);
                        it = _socket.erase(it);
                        std::cout << "Socket disconnesso" << std::endl;
                    } else {
                        buffer[bytesRead] = '\0';

                        // Verifica del dominio per il client esistente
                        int domainResult = getpeername(socketInfo.socket, (struct sockaddr*)&addr, &addrLen);
                        if (domainResult == 0) {
                            domainResult = getnameinfo((struct sockaddr*)&addr, addrLen, clientDomain, sizeof(clientDomain), NULL, 0, NI_NAMEREQD);
                            if (domainResult == 0) {
                                if (!isAllowedDomain(clientDomain, socketInfo.allowed_domain)) {
                                    std::cerr << "Connessione rifiutata da " << clientDomain << std::endl;
                                    close(socketInfo.socket);
                                    it = _socket.erase(it);
                                } else {
                                    _server[clientDomain].run(buffer, socketInfo.socket, socketInfo.client_domain, socketInfo.port);
                                }
                            } else {
                                perror("Errore nella risoluzione del dominio");
                                close(socketInfo.socket);
                                it = _socket.erase(it);
                                std::cout << "Socket disconnesso" << std::endl;
                            }
                        } else {
                            perror("Errore nel recupero dell'indirizzo del peer");
                            close(socketInfo.socket);
                            it = _socket.erase(it);
                            std::cout << "Socket disconnesso" << std::endl;
                        }
                    }
                }
            }
        }
    }
}