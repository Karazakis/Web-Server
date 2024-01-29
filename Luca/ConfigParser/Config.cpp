#include "Config.hpp"

Config::Config(char *filename, std::multimap<std::string, std::string> defaul_env) : _file(filename), _default_env(defaul_env)
{
    takeEnvFromFile(filename);
}

void Config::mergeEnv()
{

}

bool Config::checkEnv()
{

}

void Config::takeEnvFromFile(char *filename)
{
    if (filename[0]) {
        Parser parser(filename);
        _env = parser.getEnv();
        mergeEnv();
    } else {
        _env.push_back(_default_env);
    }

    if (!checkEnv()) {
        throw NoValidServerException();
    }
}

std::vector< std::multimap<std::string, std::string> > Config::getEnv()
{
    return(_env);
}