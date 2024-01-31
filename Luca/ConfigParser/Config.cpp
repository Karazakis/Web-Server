#include "Config.hpp"

Config::Config(char *filename, std::multimap<std::string, std::string> defaul_env) : _file(filename), _default_env(defaul_env)
{
    takeEnvFromFile(filename);
}

Config::~Config() {
    // Clean up resources if necessary
}

Config::Config(Config const &src) {
    // Implement copy constructor if necessary
    // Deep copy _file, _default_env, and _env from src
}

Config &Config::operator=(Config const &rhs) {
    if (this != &rhs) {
        // Implement assignment operator if necessary
        // Deep copy _file, _default_env, and _env from rhs
    }
    return *this;
}

void Config::mergeEnv()
{

}

bool Config::checkEnv()
{
 // Implement the logic to check the environment
    return true; // or false, depending on your logic
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