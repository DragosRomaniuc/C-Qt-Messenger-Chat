#ifndef CLIENT_H
#define CLIENT_H
#include "tcpclient.h"
#include <QWidget>
#include "login.h"
#include <QtCore>
#include "mythread.h"
#include "thread"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    Client(TCPClient& _newclient);
    bool sendData(std::string username, std::string parola,std::string address,std::string port);
    ~Client();
    std::string info,stats;
    std::string boxMessage;
    TCPClient* client;
    MyThread *mThread;
    bool clicked,connected,connectedrecv;
    MyThread *t;
    std::thread *t1;
    std::string recvmsg;
    login *loginform;
    void loginfunct();
    std::string chatwith;
private slots:
    void displayMyMessage(std::string, std::string);
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

protected:
//      void showEvent(QShowEvent *ev);
signals:
    void Speak(QString word);
private:
    int count;
    Ui::Client *ui;
    std::string username;
    std::string parola;
    std::string address;
    std::string port;
    std::string status;
public slots:
    void Listen(QString word);
    void onNumberChanged(int);

};

#endif // CLIENT_H
