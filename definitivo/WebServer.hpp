#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP
# include "ConfigParser/Config.hpp"
# include "Server.hpp"
# include "Socket/LibSocket.hpp"
# include "RequestHandler/RequestHandler.hpp"
# include "Responder/Responder.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <cstring>
# include <sys/socket.h>

class Server;

class SocketInfo {
    public:
        SocketInfo();
        SocketInfo(int port, std::vector< std::string > allowed_doman);
        SocketInfo(int &sock, int por, std::string doman, std::vector< std::string > allowed_doman);
        ~SocketInfo();

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
        ~WebServer();
        
        WebServer &operator=(WebServer const &rhs);
        void closeAllServer();
        std::multimap<std::string, std::string> loadDefaultEnv();
        bool isAllowedDomain(char *domain, std::vector< std::string > allowed_domain);
        void run();

    private:
        std::map< std::string, Server * > _server;
        std::vector< std::multimap< std::string, std::string > > _env;
        std::vector< SocketInfo > _socket;
};

#endif
