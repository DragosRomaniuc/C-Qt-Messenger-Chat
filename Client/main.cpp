#include "clientretele.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientRetele w;
    w.show();


    return a.exec();
}
