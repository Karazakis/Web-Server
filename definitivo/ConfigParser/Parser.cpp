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

}

void Parser::takeServer()
{

}

void Parser::takeEnv()
{

}

std::vector< std::multimap<std::string, std::string> > Parser::getEnv()
{
    return(_env);
}