#include "WebServer.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        try
        {
            WebServer server(argv[1]);
            server.run();
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: config file non valido:" << e.what() << '\n';
        }
    }
    else if (argc == 1)
    {
        try
        {
            WebServer server("");
            server.run();
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: config file non valido:" << e.what() << '\n';
        }
    }
    else
        std::cout << "Troppi argomenti"  << std::endl;
}