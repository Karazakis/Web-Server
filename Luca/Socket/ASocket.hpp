#ifndef ASOCKET_HPP
# define ASOCKET_HPP

#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>
#include <fcntl.h> // For fcntl, F_GETFL, F_SETFL, and O_NONBLOCK
#include <unistd.h> // for close()

class ASocket 
{
    protected:
        struct sockaddr_in address;
        int sock;
    public:
        ASocket(int domain, int service, int protocol, int port, u_long interface);
        
        
        virtual void connect_to_network(int sock, struct sockaddr_in address) = 0;
        void test_connection(int item_to_test);

        struct sockaddr_in getAddr();
        int getSock();
        void setAddr(struct sockaddr_in address);
        void setSock(int sock);
        //void setSocketNonBlocking2();
        virtual void closeSocket();
};

#endif