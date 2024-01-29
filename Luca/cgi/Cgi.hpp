#ifndef CGI_HPP
# define  CGI_HPP
# include "../WebServer.hpp"
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class Cgi
{
    public:
        Cgi(std::map<std::string, std::string> env, std::string script,int &socket, RequestHandler request);
        Cgi(Cgi const &src);
        ~Cgi();
        
        Cgi &operator=(Cgi const &rhs);
        void takeEnvp();
        void exec();

    private:
        std::map<std::string, std::string> _env;
        std::string _script;
        int &_socket;
        pid_t _cgi_proc;
        char **_envp;
};

#endif