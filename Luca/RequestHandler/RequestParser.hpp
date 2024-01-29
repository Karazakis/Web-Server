#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP
# include "../WebServer.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class RequestParser
{
    public:
        RequestParser(char *buffer);
        RequestParser(RequestParser const &src);
        ~RequestParser();

        void parseRequest(char *buffer);
        
        RequestParser &operator=(RequestParser const &rhs);
        void takeType();
        void takePath();
        void takeSetting();
        void takeBody();
        void takeQuery();
        std::string getType();
        std::string getPath();
        std::string getSetting();
        std::string getQuery();
        std::string getBody();

    private:
        bool is_cgi;
        std::string _type;
        std::string _path;
        std::string _setting;
        std::string _query;
        std::string _body;
};

#endif