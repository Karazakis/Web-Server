#include "WebServer.hpp"

WebServer::WebServer() : AServer(AF_INET, SOCK_STREAM, 0, 2522, INADDR_ANY, 10)
{
    launch();
}

void WebServer::accepter()
{
    struct sockaddr_in address = socket->getAddr();
    int addrlen =sizeof(address);
    new_socket = accept(socket->getSock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
    read(new_socket, buffer, 30000);
}

std::map<std::string, std::string> getCGIEnvironment() {
    std::map<std::string, std::string> environment;

    // REQUEST_METHOD: Metodo HTTP (GET in questo caso)
    environment["SCRIPT_FILENAME"] = "script.cgi";

    environment["REQUEST_METHOD"] = "GET";

    // QUERY_STRING: Stringa di query (vuota in questo caso)
    environment["QUERY_STRING"] = "";

    // CONTENT_TYPE: Tipo di contenuto (non necessario in questo caso)
    environment["CONTENT_TYPE"] = "";

    // CONTENT_LENGTH: Lunghezza del corpo della richiesta (0 in questo caso)
    environment["CONTENT_LENGTH"] = "0";

    // HTTP_USER_AGENT: Header User-Agent (puoi personalizzarlo)
    environment["HTTP_USER_AGENT"] = "Custom User Agent";

    // REMOTE_ADDR: Indirizzo IP del client (puoi personalizzarlo)
    environment["REMOTE_ADDR"] = "127.0.0.1";

    // SERVER_NAME: Nome del server (puoi personalizzarlo)
    environment["SERVER_NAME"] = "localhost";

    // SERVER_PORT: Porta su cui il server sta ascoltando (personalizzala in base alle tue esigenze)
    environment["SERVER_PORT"] = "2522";

    // SERVER_SOFTWARE: Nome e versione del software del server
    environment["SERVER_SOFTWARE"] = "My Custom Server/1.0";

    environment["SERVER_PROTOCOL"] = "HTTP/1.1";
    // GATEWAY_INTERFACE: Versione del protocollo CGI
    environment["GATEWAY_INTERFACE"] = "CGI/1.1";
    
    environment["REDIRECT_STATUS"] = "200";
    return environment;
}

char    **_getEnvAsCstrArray(std::map<std::string, std::string> env_map) 
{
	char	**env = new char*[env_map.size() + 1];
	int	j = 0;
	for (std::map<std::string, std::string>::const_iterator i = env_map.begin(); i != env_map.end(); i++) {
		std::string	element = i->first + "=" + i->second;
		env[j] = new char[element.size() + 1];
		env[j] = strcpy(env[j], (const char*)element.c_str());
		j++;
	}
	env[j] = NULL;
	return env;
}

void WebServer::handler()
{
    char **envis;
    std::map<std::string, std::string> environment;
    pid_t pid = fork();
    if (pid == 0) {
        // Codice del processo figlio (CGI)
        close(STDOUT_FILENO); // Chiudi lo standard output
        dup2(new_socket, STDOUT_FILENO); // Redirigi lo standard output al socket

        // Imposta le variabili d'ambiente necessarie per il CGI
        //setenv("REQUEST_METHOD", "GET", 1);
        // Imposta altre variabili d'ambiente necessarie...
        environment = getCGIEnvironment();
        envis = _getEnvAsCstrArray(environment);
        // Definisci un array di argomenti per il tuo processo CGI
        char * const * nll = NULL;
        // Esegui il componente CGI utilizzando execve
        const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
        write(new_socket, response, strlen(response));
        execve("script.cgi", nll, envis);
        exit(0);
    } else if (pid < 0) {
        std::cerr << "Errore nella creazione del processo CGI" << std::endl;
        // Gestire l'errore...
    } else {
        // Codice del processo padre (server)
        // Attendi il termine del processo CGI, se necessario
        waitpid(pid, NULL, 0);
         // Ora puoi leggere la risposta HTTP inviata dal CGI dal socket e inviarla al client.
/*         char responseBuffer[30000];
        ssize_t bytesRead;
        std::string response;
        
        std::ofstream file( "log" );
        while ((bytesRead = read(new_socket, responseBuffer, sizeof(responseBuffer))) > 0) {
            response.append(responseBuffer, bytesRead);
            file << (bytesRead = read(new_socket, responseBuffer, sizeof(responseBuffer))) << std::endl;
            file << "test" << std::endl;
        }
        file << "test" << std::endl;
        file.close(); */
        // Invia la risposta HTTP al client
        //write(new_socket, response.c_str(), response.length());
    }
}

void WebServer::responder()
{
   /*const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nCiao, mondo!";
    write(new_socket, response, strlen(response));*/

    //char *test = (char *)"Sporcodio";
    //write(new_socket, test, strlen(test));

    close(new_socket);
    //close(STDOUT_FILENO);
}

void WebServer::launch()
{
    while (true)
    {
        std::cout << "===========WAITING===========" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "===========DONE===========" << std::endl;
    }
    
}
