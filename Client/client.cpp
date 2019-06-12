#include "client.h"
#include "ui_client.h"
#include "iostream"
#include <string>
#include <string.h>
#include <stdio.h>
#include <QLabel>
#include "stdlib.h"
#include "tcpclient.h"
#include <thread>
#include "mutex"
#include "chrono"
using namespace std;
std::mutex mtx;

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    connect(this, SIGNAL(Speak(QString)), this, SLOT(Listen(QString)) );
    chatwith = "BROADCAST";
}


void Client::onNumberChanged(int Number){
    ui->myNumber->setText(QString::number(Number));
}

Client::~Client()
{
    delete ui;
}

//void Client::loginfunct(){
//     loginform = new login;
//    mtx.lock();
//    loginform->show();
//     mtx.unlock();
//     std::string newuser,newpass;
//     newuser = loginform->username;
//     newpass = loginform->password;
//     std::cout<<newuser<<"------------------"<



//}
void Client::Listen(QString word){
    ui->textBrowser1->append(word);
}
bool Client::sendData(std::string _username, std::string _parola,std::string _address, std::string _port){
    status = "Connected";
    count = 0;
    username = _username;
    parola = _parola;
    address=_address;
    port=_port;
    ui->username->setText(username.c_str());
    ui->serveripLabel->setText(address.c_str());
    ui->serverportLabel->setText(port.c_str());
    ui->statusLabel->setText(status.c_str());
    clicked = false;
    info = _username + ":" + _parola;
    info = "LoginCredits:" + info;
    stats = username + " connected to the server!";
    connectedrecv = true;
    t1 = new std::thread([&](){
        std::cout<<"THREAD CREATED!!";
        mtx.lock();
        client = new TCPClient;
         connected = client->conn(address,atoi(port.c_str()));
                    client->send_data(stats);
                    std::this_thread::sleep_for(chrono::milliseconds(300));
                    client->send_data(info);
                    info.clear();
                    recvmsg.clear();
mtx.unlock();
    while(1){
        if(connectedrecv){
        recvmsg = client->receive(1024);
        if(!recvmsg.empty()){
            std::cout<<"am primit de la thread "<<recvmsg<<std::endl;
            if(recvmsg.compare("NotAllowedToLogIn")==0){
                count=count+10;
                connectedrecv = false;
            }
            if(count == 1){

                this->show();
            }
//            recvmsg = "[Server] " + recvmsg;
//            recvmsg = "[Server] " + recvmsg;
            QString qstr = QString::fromStdString(recvmsg);
            emit Speak(qstr);
        }
        count++;
    }
    }});
//         t = new MyThread(address,atoi(port.c_str()),info);
//         t->Create();

//        std::this_thread::sleep_for(chrono::milliseconds(500));
//         client = new TCPClient;
//          std::string receivedMsg;
//             client->conn(address,atoi(port.c_str()));

//             client->send_data(info);


//            receivedMsg = client->receive(512);
//            if(!receivedMsg.empty() ){
//                  displayMyMessage(receivedMsg, "[Server]: ");
//                     }

//


}



void Client::displayMyMessage(std::string message, std::string pre){
    message = pre + message;
    QString qstr = QString::fromStdString(message);
    ui->textBrowser1->append(qstr);

}

void Client::on_pushButton_2_clicked()
{
    clicked = true;
    QString message = ui->textEditObj->toPlainText();
    std::string newMessage = message.toStdString();
//    mtx.lock();
    if(newMessage.compare("/onlineusers")!=0){
         newMessage=chatwith +':'+newMessage;
    }
    client->send_data(newMessage);

    ui->textEditObj->setText("");
    newMessage = newMessage.substr(chatwith.length());

    //MESSAGE FROM [ME];
    newMessage = newMessage.substr(1);
    displayMyMessage(newMessage, "");
//    mtx.unlock();
    clicked=false;

//    if(message.toStdString().compare("/onlineusers")==0){
//        displayMyMessage("Online users are : ", "");
//    }

//   std::string receivedMsg = client->receive(512);
//    if(!receivedMsg.empty() ){
//    displayMyMessage(receivedMsg, "");
//        }
}

void Client::on_pushButton_4_clicked()
{
    if(ui->chatwithEdit->toPlainText().toStdString().length()<3){
        chatwith = "BROADCAST";
        ui->chatwithLabel->setText("BROADCAST");
        ui->chatwithEdit->setText("");
    }else{
      chatwith = ui->chatwithEdit->toPlainText().toStdString();
      ui->chatwithLabel->setText(ui->chatwithEdit->toPlainText());
      ui->chatwithEdit->setText("");
      size_t found = chatwith.find_first_of(':');
      ui->textBrowser1->clear();
      ui->textBrowser1->setText("[SERVER]: Your conversation history:");
      std::string sendHistory = "SendHistory" + username + chatwith.substr(0,found);
      client->send_data(sendHistory);
    }
}

void Client::on_pushButton_3_clicked()
{
    ui->chatwithLabel->setText("BROADCAST");
    chatwith = "BROADCAST";
}

void Client::on_pushButton_clicked()
{
connectedrecv = false;
    client->send_data("PleaseDisconnectMe");
    ui->textBrowser1->clear();
    ui->statusLabel->setText("Disconnected");
    ui->chatwithLabel->setText("Nobody");
    ui->pushButton_2->setEnabled(false);


}

void Client::on_pushButton_5_clicked()
{
    ui->textBrowser1->clear();
}
