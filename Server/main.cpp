#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "TCPListener.h"
#include "fstream"
#include <stdio.h>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex mtx;


using namespace std;

void Listener_MessageReceived(TCPListener* listener, int client, string msg, int port);


bool verifica;

bool CheckUserInfo(int client, std::string msg, int port, TCPListener *listener){
    std::string username,parola;
    int i = 13;
    for(i;i<msg.length();i++){
        if(msg[i]==':') break;
        username += msg[i];

    }
    i++;
    for(i;i<msg.length();i++){
        if(msg[i]==':') break;
        parola += msg[i];

    }
    if(parola.empty() | username.empty()){
        return false;
    }
    std::string newname;
    size_t found2;
    std::cout<<"Username: "<<username<<std::endl<<"Parola: "<<parola<<std::endl;
    std::string numeport = username+':'+to_string(port);
    std::map<std::string, int>::iterator it;
            string line;
            size_t find;
            ifstream myfile ("/home/dragos/Desktop/DeTrimis/Proiect2Interfata/users.txt");
            if(myfile.is_open()){
                while(getline(myfile, line)){
                    find = line.find(':');
                    string name = line.substr(0,username.length());
                    if(find==username.length()){
                        if(name.compare(username)==0){
                            find = line.find(parola);
                            if(find!=std::string::npos){
                                for (it = TCPListener::sessions.begin(); it != TCPListener::sessions.end(); it++) {


                                    found2 = it->first.find_first_of(':');
                                    newname = it->first.substr(0, found2);

                                    if (newname.compare(name) == 0) {
                                        std::cout<<std::endl<<name<<" a incercat sa se conecteze dar este deja online!";
                                        return false;
                                    }


                                }
                                TCPListener::sessions.insert( pair<std::string, int>(numeport, client) );
                                std::cout<<std::endl<<name<<" s-a conectat la ip-ul 127.0.0.1 !";
                                return true;
                            }
                            else{
                                std::cout<<"ELSEEEEEEEEEEEEEEEEEEEEEEe";
                                return false;
                            }
                        }
                    }
                    std::cout<<"caut...";
                }
                cout<<"Please enter a valid username by the following example: login : username"<<endl;
                myfile.close();
            }
    return false;
}




std::string getOnlineUsers(){
    std::string onlineusers;
    std::map<std::string, int>::iterator it;
    for (it = TCPListener::sessions.begin();  it != TCPListener::sessions.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
        if (it->first.compare("test") != 0) {
            onlineusers = it->first +", " + onlineusers;

//                    mtx.lock();
//                    listener->Send(client,onlineusers);
//                    mtx.unlock();
        }
    }
    return onlineusers;
}

inline bool txtexists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


int main()
{

    TCPListener server("127.0.0.1", 54100, Listener_MessageReceived);
    server.Run();

    std::cout << "Hello world!" << endl;
    return 0;
}

void Listener_MessageReceived(TCPListener *listener, int client, std::string msg, int port){
    std::cout<<"In functie---"<<msg<<"---------"<<std::endl;
//    std::cout<<msg.substr(0,12)<<std::endl;
    std::string newInfo = msg.substr(0,12);
    std::string username;
    std::string parola;
    std::string onlineusers = "";
//    std::cout<<"am primit " <<msg<<std::endl;
    if(newInfo.compare("LoginCredits")==0) {

    int i = 13;
    for(i;i<msg.length();i++){
        if(msg[i]==':') break;
        username += msg[i];

    }
    i++;
    for(i;i<msg.length();i++){
        if(msg[i]==':') break;
        parola += msg[i];

    }
        verifica = CheckUserInfo(client, msg,port,listener);
        if (!verifica) {
            listener->Send(client, "NotAllowedToLogIn");
        } else {
            listener->Send(client, "AllowedToLogIn");

        }
    }else{
        if (msg.compare("/onlineusers") == 0) {
            std::cout<<"Am trimis online users!";
           onlineusers = getOnlineUsers();
           std::cout<<std::endl<<onlineusers<<"  si   "<<onlineusers.length()<<std::endl;
            listener->Send(client, onlineusers);
        }else if (msg.find("connected") == std::string::npos) {
            std::cout << "Trimit 5";
            int sum = 0;
            std::string cautatxt;
            cautatxt = msg.substr(0,11);
            std::string sendto;
            if(cautatxt.compare("SendHistory")==0){
                sendto = msg.substr(11);
                for(int wk= 11 ; wk<msg.length() ; wk++){
                    std::cout<<msg[wk];
                    sum = (int)msg[wk] + sum;
                }
                if(txtexists(std::to_string(sum))){
                    std::string filetoread2 = "/home/dragos/Desktop/DeTrimis/Proiect2Interfata/cmake-build-debug/1" + std::to_string(sum);
                    std::cout<<"DADADADADA EXISIIIISlolololololololololoTAITAIAAAA";
                    std::ifstream file(std::to_string(sum).c_str());
                    std::string str;
                    while (getline(file, str))
                    {
                        std::cout<<"CITESEC"<<std::endl;

                        listener->Send(client, str);
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }
                }
            }


            //mesaj normal

            std::cout<<std::endl<<msg.substr(0,10)<<std::endl;
            listener->Send(client, "Message Sent!");

        }



    }
//    }



//    std::cout<<"New message from port "<<port<<":";
//    std::cout<<"Am primit de la Client"<<msg<<std::endl;
//    if(newInfo.compare("LoginCredits")!=0) {
//        newInfo.clear();
        std::string mess = "Message sent! \n";
//        listener->Send(client, mess);
//    }

}