#include "clientretele.h"
#include "ui_clientretele.h"
#include "tcpclient.h"
#include "string"
#include "string.h"
#include "iostream"
#include "client.h"
#include "thread"
using namespace std;

ClientRetele::ClientRetele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRetele)
{
    ui->setupUi(this);
}

ClientRetele::~ClientRetele()
{
    delete ui;
}




void ClientRetele::on_usernameText_textChanged(const QString &arg1)
{
    username = arg1.toStdString();
}

void ClientRetele::on_connectButton_clicked()
{
    int ok=1;
    if(portHelp.empty()){
        ui->pleaselogin->setText("Please complete the Port field!");
        ok=0;

    }
    if(address.empty()){
        ui->pleaselogin->setText("Please complete the address field!");
        ok=0;
    }
    if(parola.empty()){
        ui->pleaselogin->setText("Please complete the password field!");
        ok=0;
    }
    if(username.empty()){
        ui->pleaselogin->setText("Please complete the username field!");
        ok=0;
    }
    if(ok==1){
    std::cout<<"Trying to connect to address: "<<address<<" with port "<<stoi(portHelp)<<std::endl;
            nou = new Client;
            canconnect = nou->sendData(username, parola, address, portHelp);
//               nou->show();



//

}




//            nou->setUserPassword(username, parola, address, portHelp);

       };
//       std::string recieved = c.receive(1024);
//       std::cout<<recieved;



void ClientRetele::on_portText_textChanged(const QString &arg1)
{
    portHelp = arg1.toStdString();

}

void ClientRetele::on_serveripText_textChanged(const QString &arg1)
{
    address = arg1.toStdString();
}

void ClientRetele::on_passwordText_textChanged(const QString &arg1)
{
    parola = arg1.toStdString();
}
