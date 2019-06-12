#ifndef TCPLISTENER_H
#define TCPLISTENER_H
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <map>
class TCPListener;

//forward declaration of the class
typedef void(*MessageRecieveHandler)(TCPListener* listener, int socketId, std::string msg, int port);


//callback to data received
class TCPListener
{
public:
    TCPListener(std::string ipAddress, int port, MessageRecieveHandler handler);
    ~TCPListener();
    //Send a message to the specified client
    void Send(int clientSocket, std::string msg);

    bool Init();
    void disconectClient(int client);
    void Run();
    static std::map<std::string, int> sessions;
    static std::vector<std::string> usericonectati;
    void Cleanup();
    int read_from_client (int filedes, int port);
    bool verifica;
    std::string newInfo;
    int foundclient;
    std::string newname2;
    std::string conversationfiletocreate;
    //Initialize
    //Create a socket
    //Wait fo a connection
    //Receive loop
    //send back message
    //cleanup.
//    bool CheckUserInfo(int client, std::string msg);
private:
    int CreateSocket();
    int WaitForConnection(int socket);
    std::string             m_ipAddress;
    int                    m_port;
    MessageRecieveHandler   MessageReceived;
    std::vector<std::string> connectedUsers;

};

#endif // TCPLISTENER_H