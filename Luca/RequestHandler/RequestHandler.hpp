#ifndef REQUESTHANDLER_HPP
# define REQUESTHANDLER_HPP
# include "../WebServer.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class RequestHandler
{
    public:
        RequestHandler(char *buffer, std::string domain, int por);
        RequestHandler(RequestHandler const &src);
        ~RequestHandler();
        
        
        RequestHandler &operator=(RequestHandler const &rhs);
        void execRequest();
        bool isCgi();
        std::string getResponseHeader();
        std::string getResponseBody();
        void parseRequest(char *buffer);

    private:
        bool is_cgi;
        std::multimap<std::string, std::string> _env;
        std::vector< std::multimap<std::string, std::string> > _location_setting;
        std::string _type;
        std::string _path;
        std::string _setting;
        std::string _query;
        std::string _body;
        std::string _body_reponse;
        
        int _status;
};

#endif