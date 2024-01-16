#include "Config.hpp"

Config::Config(char *filename, std::multimap<std::string, std::string> defaul_env) : _file(filename), _default_env(defaul_env)
{
    takeEnvFromFile();
}

void Config::mergeEnv()
{

}

bool Config::checkEnv()
{

}

void Config::takeEnvFromFile()
{
    if(_file[0])
    {
        Parser parser(_file);
        _env = parser.getEnv();
        mergeEnv();
    }
    else
        _env.push_back(_default_env);
    if (!checkEnv())
        throw NoValidServerException();
}

std::vector< std::multimap<std::string, std::string> > Config::getEnv()
{
    return(_env);
}