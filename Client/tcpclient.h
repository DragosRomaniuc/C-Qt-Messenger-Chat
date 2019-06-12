#ifndef TCPCLIENT_H
#define TCPCLIENT_H


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;


class TCPClient{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    TCPClient();
    bool conn(std::string, int);
    bool send_data(std::string data);
    std::string receive(int);
//    std::string getAddress();
};


#endif // TCPCLIENT_H
