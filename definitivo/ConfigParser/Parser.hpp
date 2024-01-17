#ifndef PARSER_HPP
# define PARSER_HPP
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>

class Parser
{
    public:
        Parser(char *filename);
        Parser(Parser const &src);
        ~Parser();

        Parser &operator=(Parser const &rhs);
        void takeFile(char *inputfile);
        void takeServer();
        void takeEnv();
        std::vector< std::multimap<std::string, std::string> > getEnv();
        void checkBrackets();

        class NotExistingFileException : std::exception { virtual const char* what() const throw() { return "File non esiste"; } };
        class WrongFileException : std::exception { virtual const char* what() const throw() { return "File non valido"; } };
        class NoClosingBracketException : std::exception { virtual const char* what() const throw() { return "Non hai chiuso correttamente le parentesi"; } };

    private:
        std::vector<std::string> _file;
        std::vector<std::string> *_server;
        std::vector< std::multimap<std::string, std::string> > _env;
};

#endif