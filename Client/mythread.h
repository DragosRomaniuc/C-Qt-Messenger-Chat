#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QtCore>
#include <QThread>
#include "tcpclient.h"
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include "tcpclient.h"
using namespace std;

class MyThread {
  public:
    int sock;
    pthread_t tid;
    struct sockaddr_in server;
    void sum(std::string x, int y, std::string z);
  private:
    static pthread_mutex_t mutex;

  public:
    std::string x,z;
    int y;
    std::string recvmsg;
    void* print_message(void* );
    MyThread(std::string x, int y, std::string z);
    int Create();
    int Join();
    void Recv();
    TCPClient* client;
    static int InitMutex();
    static int LockMutex(const char *identifier);
    static int UnlockMutex(const char *identifier);
};

#endif // MYTHREAD_H
