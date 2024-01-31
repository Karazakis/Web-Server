#include "WebServer.hpp"
#include "Server.hpp"

SocketInfo::SocketInfo() : socket(-1), isServer(false), port(0), socket_class(NULL) {
    // Properly initialize all members
}

SocketInfo::SocketInfo(int por, std::vector< std::string > allowed_doman)
{
    socket_class = new ListenSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10);
    socket = socket_class->getSock();
    port = por;
    allowed_domain = allowed_doman;
}

SocketInfo::SocketInfo(int sock, int por, std::string doman, std::vector< std::string > allowed_doman) : port(por), socket(sock), allowed_domain(allowed_doman)
{

}

SocketInfo::~SocketInfo(){
    delete socket_class;
}

// Function to load the default environment settings
std::multimap<std::string, std::string> WebServer::loadDefaultEnv() {
    // Implementation depends on how you want to handle default settings
    // Here is a simple example:
    std::multimap<std::string, std::string> defaultEnv;
    defaultEnv.insert(std::make_pair("default_key", "default_value"));
    // ... Add more default settings as needed ...
    return defaultEnv;
}

// Function to check if a domain is allowed
bool WebServer::isAllowedDomain(char *domain, std::vector<std::string> allowed_domain) {
    // Assuming 'domain' is a domain name that needs to be checked
    // against a list of allowed domains
    std::string domainStr(domain);
    for (const auto& allowed : allowed_domain) {
        if (domainStr == allowed) {
            return true;
        }
    }
    return false;
}

// Function to close all servers
void WebServer::closeAllServer() {
    // Close all server sockets and perform necessary cleanup
    for (auto& serverPair : _server) {
        // Assuming Server class has a method to close its sockets
        serverPair.second->closeServer(); // You need to implement this in the Server class
    }
    // Clean up any other resources associated with the WebServer
}

bool WebServer::isPortExisting(int portNumber)
{
    for (const auto& socketInfo : _socket) {
        if (socketInfo.port == portNumber) {
            return true;
        }
    }
    return false;
}

WebServer::WebServer(char *filename)
{
    std::multimap<std::string, std::string> defaul_env = loadDefaultEnv();
    Config config(filename, defaul_env);
    _env = config.getEnv();
    for(int i = 0; i < _env.size(); i++)
    {
        Server *tmp = new Server(_env[i]);
        for (const auto& envPair : _env[i])
        {
            if (envPair.first == "server_name")
            {
                // Use envPair.second, which is the value corresponding to "server_name"
                _server[envPair.second] = tmp;
            }
        }
        for (const auto& envPair : _env[i])
            if (envPair.first == "port")
            {
                int portNumber = std::stoi(envPair.second);
                if (!isPortExisting(portNumber))
                {
                    // Find allowed domains for this port
                    std::vector<std::string> allowedDomains;
                    // Assuming you have a way to get allowed domains for this port
                    // Populate allowedDomains here based on your configuration
                    _socket.push_back(SocketInfo(portNumber, allowedDomains));
                }
            }
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
                        setSocketNonBlocking(newClientSocket);
                        domainResult = getpeername(newClientSocket, (struct sockaddr*)&addr, &addrLen);
                        if (domainResult == 0) {
                            domainResult = getnameinfo((struct sockaddr*)&addr, addrLen, clientDomain, sizeof(clientDomain), NULL, 0, NI_NAMEREQD);
                            if (domainResult == 0) {
                                if (!isAllowedDomain(clientDomain, socketInfo.allowed_domain)) {
                                    std::cerr << "Connessione rifiutata da " << clientDomain << std::endl;
                                    close(newClientSocket);
                                } else {
                                    std::cout << "Nuova connessione accettata su porta " << socketInfo.port << " e dominio " << clientDomain << std::endl;
                                    _socket.push_back(SocketInfo(newClientSocket, socketInfo.port, clientDomain, socketInfo.allowed_domain));
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
                                } else 
                                {
                                    int socket = socketInfo.socket; // Copy the value to a temporary variable
                                    _server[clientDomain]->run(buffer, socket, socketInfo.client_domain, socketInfo.port);
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