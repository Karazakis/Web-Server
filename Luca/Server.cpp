#include "Server.hpp"

void Server::run(char *buffer, int &socket, std::string domain, int port)
{
    takeLocation();
    RequestHandler request(buffer, domain, port);
    // Optionally set _env and _location_setting via other methods if needed
    // request.setEnv(_env);
    // request.setLocationSetting(_location_setting);
    Responder(request, socket);
}