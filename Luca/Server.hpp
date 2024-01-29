#ifndef SERVER_HPP
# define SERVER_HPP
# include "WebServer.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class Server
{
    public:
        Server(std::multimap<std::string, std::string> _env);
        Server(Server const &src);
        ~Server();
        
        Server &operator=(Server const &rhs);
        void takeLocation();

        void run(char *buffer, int &socket, std::string domain, int port);
        std::vector< ListenSocket > socket_container;

    private:
        std::multimap<std::string, std::string> _env;
        std::vector< std::multimap<std::string, std::string> > _location_setting;
        std::string _request;
        std::string _response_header;
};

#endif