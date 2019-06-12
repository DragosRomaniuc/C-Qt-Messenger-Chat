#include "mythread.h"
#include <QtCore>
#include <iostream>
#include <string>
#include <string.h>
#include "tcpclient.h"
#include "thread"
#include "chrono"

using namespace std;

//Need to actually "allocate" static member
pthread_mutex_t MyThread::mutex;

MyThread::MyThread(std::string x, int y, std::string z):x(x),y(y),z(z){



}

void *Recv(){
    float i=1;
    while(1){
        i+=0.1;
        std::cout<<i;
    }
}

//void creaza(std::string x, int y, std::string z){

//        while(1)
//}
void MyThread::sum(std::string x, int y, std::string z){
    TCPClient *client2 = new TCPClient;
    client2->conn(x,y);
}
void* MyThread::print_message(void*) {
    client = new TCPClient;
    client->conn(x,y);
    client->send_data("ana are mere");
//    creaza(x,y,z);
//     TCPClient *client = new TCPClient;
//    client->conn(x,y);
//        client->send_data(z);



//        std::cout<<recvmsg;
       /* std::this_thread::sleep_for(std::chrono::milliseconds(500));*/
         cout << "Threading\n";
//         this->sum(x,y,z);


}


int MyThread::Create() {
  int tret=0;

  //Supercreepy typecast
  typedef void * (*THREADFUNCPTR)(void *);
  pthread_create(&this->tid, NULL, (THREADFUNCPTR) &MyThread::print_message, NULL);

  if(tret) {
    cerr << "Error while creating threads." << endl;
    return tret;
  }
  else {
    cout << "Thread successfully created." << endl;
    return 0;
  }
}

int MyThread::Join() {
  pthread_join(this->tid, NULL);
  return 0;
}

int MyThread::InitMutex() {

  if(pthread_mutex_init(&MyThread::mutex, NULL) < 0) {
    cerr << "Error while initializing mutex" << endl;
    return -1;
  }
  else {
    cout << "Mutex initialized." << endl;
    return 0;
  }
}

/*
    LockMutex():
        Blocks until mutex becomes available
*/
int MyThread::LockMutex(const char *identifier) {
  cout << identifier << " is trying to acquire the lock..." << endl;
  if(pthread_mutex_lock(&MyThread::mutex) == 0) {
    cout << identifier << " acquired the lock!" << endl;
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to acquire the lock" << endl;
   return -1;
  }
}

int MyThread::UnlockMutex(const char *identifier) {
  cout << identifier << " is trying to release the lock..." << endl;
  if(pthread_mutex_unlock(&MyThread::mutex) == 0) {
    cout << identifier << " released the lock!" << endl;
    return 0;
  }
  else {
   cerr << "Error while " << identifier << " was trying to release the lock" << endl;
   return -1;
  }
}
