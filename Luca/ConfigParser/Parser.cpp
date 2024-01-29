#include"Parser.hpp"

Parser::Parser(char *filename)
{
    takeFile(filename);
    takeServer();
    takeEnv();
}

void Parser::checkBrackets()
{

}

void Parser::takeFile(char *inputfile) 
{
    std::ifstream file(inputfile);
    std::string line;

    if (!file.is_open()) {
        throw NotExistingFileException();
    }

    while (std::getline(file, line)) {
        _file.push_back(line);
    }

    file.close();
}

void Parser::takeServer()
{

}

void Parser::takeEnv() {
    std::multimap<std::string, std::string> currentEnv;

    for (const auto& line : _file) {
        // Assuming each server block starts with a specific marker, e.g., "[Server]"
        if (line == "[Server]") {
            if (!currentEnv.empty()) {
                // If there's an existing server configuration, add it to the vector
                _env.push_back(currentEnv);
                currentEnv.clear();
            }
            continue; // Skip the marker line
        }

        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            currentEnv.insert(std::make_pair(trim(key), trim(value))); // Insert into current environment map
        }
    }

    // Add the last server configuration if it exists
    if (!currentEnv.empty()) {
        _env.push_back(currentEnv);
    }
}

// Helper function to trim whitespace from strings
std::string Parser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector< std::multimap<std::string, std::string> > Parser::getEnv()
{
    return(_env);
}