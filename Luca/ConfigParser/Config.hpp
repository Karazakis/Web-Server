#ifndef CONFIG_HPP
# define CONFIG_HPP
# include "Parser.hpp"

class Config
{
    public:
        Config(char *filename, std::multimap<std::string, std::string> defaul_env);
        Config(Config const &src);
        ~Config();

        Config &operator=(Config const &rhs);
        void takeEnvFromFile(char *filename);
        bool checkEnv();
        void mergeEnv();

        std::vector< std::multimap<std::string, std::string> > getEnv();
        class NoValidServerException : std::exception { virtual const char* what() const throw() { return "Non è stata trovata una configurazione server valida"; } };

    private:
        char *_file;
        std::multimap<std::string, std::string> _default_env;
        std::vector< std::multimap<std::string, std::string> > _env;
};

#endif