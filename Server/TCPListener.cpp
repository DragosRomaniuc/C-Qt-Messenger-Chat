//
// Created by dragos on 23.11.2018.
//

#include "TCPListener.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#define MAX_BUFFER_SIZE (49152)
#define PORT    54100
#define MAXMSG  512
#include <initializer_list>
#include <map>
#include <fstream>

TCPListener::TCPListener(std::string ipAddress, int port, MessageRecieveHandler handler) : m_ipAddress(ipAddress), m_port(port), MessageReceived(handler)
{
    //ctor
}

TCPListener::~TCPListener()
{
//    Cleanup();
}


std::map<std::string,int> TCPListener::sessions = {{"test",1}};
std::vector<std::string> TCPListener::usericonectati = {{"test"}};

void TCPListener::Send(int clientSocket, std::string msg){

    send(clientSocket, msg.c_str(), msg.size()+1, 0);
//    std::cout<<msg<<"1";

}

void TCPListener::disconectClient(int client){
    close(client);
    std::cout<<std::endl<<"CLIENT DISCONECTED"<<std::endl;
}
int TCPListener::read_from_client (int filedes, int port)
{
    char buffer[MAXMSG];
    int nbytes;
    memset(buffer, 0 , MAXMSG);
    nbytes = read (filedes, buffer, MAXMSG);
    if (nbytes < 0)
    {
        /* Read error. */

        perror ("read");
        exit (EXIT_FAILURE);
    }
    else if (nbytes == 0)
        /* End-of-file. */
        return -1;
    else
    {
        /* Data read. */


        if (MessageReceived != NULL) {
            MessageReceived(this, filedes, std::string(buffer, 0, nbytes), port);
        }
//        std::cout<<buffer;
        return 0;
    }
}

//bool TCPListener::CheckUserInfo(int client, std::string msg){
//    std::string username,parola;
//    int i = 13;
//    for(i;i<msg.length();i++){
//        if(msg[i]==':') break;
//        username += msg[i];
//
//    }
//    i++;
//    for(i;i<msg.length();i++){
//        if(msg[i]==':') break;
//        parola += msg[i];
//
//    }
//    if(parola.empty() | username.empty()){
//        return false;
//    }
//    std::cout<<"Username: "<<username<<std::endl<<"Parola: "<<parola<<std::endl;
//    return true;
//}
//
//
//bool CheckUserInfo(int client, std::string msg){
//    std::string username,parola;
//    int i = 13;
//    for(i;i<msg.length();i++){
//        if(msg[i]==':') break;
//        username += msg[i];
//
//    }
//    i++;
//    for(i;i<msg.length();i++){
//        if(msg[i]==':') break;
//        parola += msg[i];
//
//    }
//    if(parola.empty() | username.empty()){
//        return false;
//    }
//    std::cout<<"Username: "<<username<<std::endl<<"Parola: "<<parola<<std::endl;
//    return true;
//}



inline bool txtexists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}




void TCPListener::Run(){
    char buf[MAX_BUFFER_SIZE];
    struct sockaddr_in clientname;
    size_t size;
    while(1) {
        int listening = CreateSocket();
        if (listening == -1) {
            std::cout<<"Eroare la creare socketului;";
            break;
        }

        fd_set master;
        FD_ZERO(&master);
        FD_SET(listening, &master);

//            while(true){
//                fd_set copy = master;
//                int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
//                for(int i = 0; i<socketCount ; ++i){
//                    int sock = copy.fds_bits[i];
//
//
//                }
//            }

        while (1)
        {
            /* Block until input arrives on one or more active sockets. */
//            read_fd_set = active_fd_set;
            fd_set copy = master;
            if (select (FD_SETSIZE, &copy, NULL, NULL, NULL) < 0)
            {
                perror ("select");
                exit (EXIT_FAILURE);
            }

            /* Service all the sockets with input pending. */
            for (int i = 0; i < FD_SETSIZE; ++i)
                if (FD_ISSET (i, &copy))
                {
                    if (i == listening)
                    {
                        /* Connection request on original socket. */

                        socklen_t clilen = sizeof(clientname);
                        int newClient = accept (listening,
                                      (struct sockaddr *) &clientname,
                                      &clilen);
                        std::cout<<"Server: connected from host: "<<inet_ntoa (clientname.sin_addr)<<" with port: "<<ntohs (clientname.sin_port)<<std::endl;


                        if (newClient< 0)
                        {
                            perror ("accept");
                            exit (EXIT_FAILURE);
                        }

                        FD_SET (newClient, &master);
                        std::string welcomeMsg = "Welcome to the server!";
                        send(newClient, welcomeMsg.c_str(), welcomeMsg.size()+1, 0);

                    }
                    else {
                        /* Data arriving on an already-connected socket. */
//                        if (read_from_client (i,ntohs(clientname.sin_port)) < 0)
//                        {
//                            close (i);
//                            FD_CLR (i, &master);
//                        }
                        char buffer[MAXMSG];
                        int nbytes;
                        memset(buffer, 0 , MAXMSG);
                        nbytes = recv(i, buffer, MAXMSG, 0);

                        struct sockaddr_in addr;
                                        socklen_t addr_size = sizeof(struct sockaddr_in);
                                        int res = getpeername(i, (struct sockaddr *)&addr, &addr_size);
                                        int newport = ntohs(addr.sin_port);
                                        std::string newbuffer = std::to_string(newport) + ": " + buffer + '\n';
                                        std::string mesajprivat;
                                        std::string fromwho;
                        int privateclient = -1;

                        if (nbytes <= 0)
                        {
                            /* Read error. */
                                close(i);
                            FD_CLR (i, &master);
//                            perror ("read");
//                            exit (EXIT_FAILURE);
                        }
                        else
                        {
                            std::string chatwith;
                            if(std::string(buffer).substr(0,10).compare("BROADCAST:")==0){
                                chatwith="BROADCAST";
                            }else {


                                std::size_t found2;
                                std::size_t found = std::string(buffer).find_first_of(':');
                                found = std::string(buffer).find_first_of(':', found + 1);
                                std::string newname, newport2;
                                std::map<std::string, int>::iterator it;
                                for (it = TCPListener::sessions.begin(); it != TCPListener::sessions.end(); it++) {


                                    found2 = it->first.find_first_of(':');
                                    newname = it->first.substr(0, found2);
                                    newport2 = it->first.substr(found2 + 1, it->first.length());
                                    if (newport2.compare(std::to_string(newport)) == 0) {
                                        break;
                                    }


                                }
                                chatwith = std::string(buffer).substr(0, found);
                                fromwho = newname + ':' + newport2;
                                std::string detrimis2;
                                found = std::string(buffer).find_first_of(':');
                                found = std::string(buffer).find_first_of(':', found + 1);
                                detrimis2 = std::string(buffer).substr(chatwith.length());
//                                std::cout<<detrimis2.substr(found,detrimis2.size());
                                std::cout<<std::endl<< "DEtrimis2 este:" << detrimis2<<" iar bufferul este "<<buffer;
                                std::string deTrimis = "[Mesaj privat de la " + fromwho + "]: " + detrimis2;
                                foundclient = 0;


                                std::string onlineusers;

                                for (it = TCPListener::sessions.begin(); it != TCPListener::sessions.end(); it++) {

                                    if (it->first.compare(chatwith) == 0) {
                                        found2 = it->first.find_first_of(':');
                                        newname2 = it->first.substr(0, found2);
                                        privateclient = it->second;
                                        foundclient = 1;
                                        break;
                                    }
                                }
//                                if (foundclient == 1) {
//                                    found = std::string(buffer).find(':');
                                std::size_t found5 = std::string(buffer).find("12345");
                                if (found!=std::string::npos) {
                                    found5 = std::string(buffer).find(':');

                                    newname2 = std::string(buffer).substr(0,found5);
                                }
//                                    std::cout<<std::endl<<std::string(buffer).substr(found)<<std::endl;
                                    //suma caracterelor ascii + nr de vocale din numere;
                                    conversationfiletocreate = newname+newname2;


                                    int sum = 0;
                                    for(int wk= 0 ; wk<conversationfiletocreate.length() ; wk++){
                                        sum = (int)conversationfiletocreate[wk] + sum;

                                    }
                                    if(txtexists(std::to_string(sum))){
                                        std::ofstream newFile(std::to_string(sum).c_str(), std::ios_base::app);
                                        newFile<<deTrimis<<std::endl;
                                    }
                                    else{
                                        std::ofstream newFile(std::to_string(sum).c_str());
                                        newFile<<deTrimis<<std::endl;
                                    }

                                std::cout<<std::endl<<"--->"<<newname<<" II trimite lui "<<newname2<<"----->"<<deTrimis<<std::endl;
                                if(privateclient != -1) {
                                    send(privateclient, deTrimis.c_str(), deTrimis.size() + 1, 0);
                                }
                                foundclient=0;
//                            }

                            }
                            /* Data read. */
                            for (int x = 0; x < FD_SETSIZE; ++x) {
                                if(FD_ISSET (x, &master)) {
                                    if (x != listening && x!= i) {
//                                        struct sockaddr_in addr;
//                                        socklen_t addr_size = sizeof(struct sockaddr_in);
//                                        int res = getpeername(x, (struct sockaddr *)&addr, &addr_size);
//                                        char *clientip = new char[20];
//                                        int newport = ntohs(addr.sin_port);
//                                        std::string clientnewip(clientip);
//                                        std::string newbuffer = std::to_string(newport) + ": " + buffer;
//                                        std::cout<<"------------------"<<buffer<<"--------------"<<std::endl;
//                                        if(newbuffer.find("LoginCredits") == std::string::npos) {
//                                        std::string newInfo = newbuffer.substr(0,12);
//
//                                        std::cout<<"-----------"<<newInfo<<"------------"<<std::endl;
                                        newInfo = std::string(buffer).substr(0,12);

                                    if(std::string(buffer).substr(0,10).compare("BROADCAST:")==0) {
                                        if (newInfo.compare("LoginCredits") != 0) {
                                            if (std::string(buffer).compare("/onlineusers") != 0) {
                                                newbuffer = "[BROADCAST MESSAGE FROM "+std::to_string(newport)+"]:" + std::string(buffer).substr(10);
                                                send(x, newbuffer.c_str(), newbuffer.size() + 1, 0);
                                            }
                                        }
                                    }else{

                                    }

//                                        }

                                    }
                                }

                            }


                            if(std::string(buffer).compare("PleaseDisconnectMe")==0){
//                                close(i);
//                                FD_CLR (i, &master);
                                std::map<std::string, int>::iterator it;
                                it = TCPListener::sessions.find(fromwho);
                                TCPListener::sessions.erase(it);

                                std::cout<<std::endl<<" CLIENT " << fromwho << " DISCONNECTED, NOT ALLOWED TO LOG IN! "<<std::endl;
                            }
                                std::cout << "------------------" << buffer << "--------------" << std::endl;
//                            std::cout << "-------setsize-----------" << FD_SETSIZE << "-------setsize-------" << std::endl;
                                if (MessageReceived != NULL) {
                                    MessageReceived(this, i, std::string(buffer, 0, nbytes),
                                                    ntohs(clientname.sin_port));
                                }

//        std::cout<<buffer;

                        }


                            }

                        }


                }
        }


        }


void TCPListener::Cleanup(){
//    WSACleanup();
}


int TCPListener::CreateSocket(){
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        std::cout<<"Can't create a socket! ;"<<std::endl;
        return -1;
    }


        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(m_port);
        inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);


       int  bindok = bind(listening, (sockaddr*)&hint, sizeof(hint));

    //	Mark the socket for listening in
       if( bindok != -1 ){
            int listenok = listen(listening, SOMAXCONN);
            if ( listenok == -1 ){
                std::cout<<"Listen() error!;"<<std::endl;
                return -1;
            }
       } else{
           std::cout<<"Bind() error; "<<std::endl;
           return -1;
       }




    return listening;
}

int TCPListener::WaitForConnection(int listening){

    int client = accept(listening, NULL, NULL);
    return client;


}