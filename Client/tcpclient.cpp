#include "tcpclient.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

TCPClient::TCPClient(){
    sock = -1;
    port=0;
    address="";
}

//std::string TCPClient:: getAddress(){
//    return address;
//}
//Connect to a host on a certani port number;

bool TCPClient::conn(std::string address, int port) {
    //create a socket if it is not already created
    if (sock == -1) {
        //Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Could not create socket");
        };

        std::cout << "Socket created!" << std::endl;
    };

    //setup address structure
    if(inet_addr(address.c_str())== -1){
        struct hostent *he;
        struct in_addr **addr_list;
        //resolve the hostname;
        if( (he = gethostbyname ( address.c_str() ) )==NULL) {
            //gethostname failed;
            herror("Failed to resolve hostname");
            std::cout << std::endl;
            return false;
        }

        addr_list = (struct in_addr**) he->h_addr_list;

        for(int i=0; addr_list[i] != NULL; ++i){
            server.sin_addr = *addr_list[i];
            std::cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<std::endl;
            break;
        }
    }else{
        server.sin_addr.s_addr= inet_addr(address.c_str());
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //connect to the server;
        if(connect (sock, (struct sockaddr *)&server, sizeof(server)) <0){
            perror("Connect failed. Error");
            return 1;
        }
        std::cout<<"Connected!"<<std::endl;
        return true;
}

bool TCPClient::send_data(std::string data) {
    //send some data
    if(send(sock, data.c_str(), strlen(data.c_str()), 0)  <0) {
        perror("Send failed: ");
        std::cout << std::endl;
        return false;
    }
    std::cout<<"Data send! "<<std::endl;
    return true;
}


std::string TCPClient::receive(int size=512){
    char buffer[size];
    std::string reply;

    //Receive a relpy from the server;
    if( recv(sock, buffer, sizeof(buffer), 0)<0){
        std::cout<<"Receive failed!!"<<std::endl;
    }


    reply = buffer;
    return reply;
}
