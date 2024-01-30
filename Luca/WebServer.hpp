#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
# include "ConfigParser/Config.hpp"
# include "./Socket/LibSocket.hpp"
# include "./RequestHandler/RequestHandler.hpp"
# include "./Responder/Responder.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <cstring>

#include <fcntl.h> // For fcntl, F_GETFL, F_SETFL, and O_NONBLOCK
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server;

class SocketInfo {
    public:
        SocketInfo();
        SocketInfo(int port, std::vector< std::string > allowed_doman);
        SocketInfo(int sock, int por, std::string doman, std::vector< std::string > allowed_doman);
        ~SocketInfo(){};

        int socket;
        bool isServer;
        int port;  // Aggiunto il numero di porta
        std::string client_domain;  // Aggiunto il dominio
        std::vector< std::string > allowed_domain;
        ListenSocket *socket_class;
};

class WebServer
{
    public:
        WebServer(char *filename);
        WebServer(WebServer const &src);
        ~WebServer(){};
        
        WebServer &operator=(WebServer const &rhs);
        void closeAllServer();
        std::multimap<std::string, std::string> loadDefaultEnv();
        bool isAllowedDomain(char *domain, std::vector< std::string > allowed_domain);
        void run();
        bool isPortExisting(int portNumber);

    private:
        std::map< std::string, Server* > _server;
        std::vector< std::multimap< std::string, std::string > > _env;
        std::vector< SocketInfo > _socket;
};

void setSocketNonBlocking(int sock) 
{
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags < 0) {
        perror("Error getting flags on socket");
        return;
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("Error setting non-blocking flag on socket");
    }
}


#endif