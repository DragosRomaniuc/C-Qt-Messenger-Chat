#ifndef CLIENTRETELE_H
#define CLIENTRETELE_H

#include <QWidget>
#include "client.h"

namespace Ui {
class ClientRetele;
}

class ClientRetele : public QWidget
{
    Q_OBJECT

public:
    explicit ClientRetele(QWidget *parent = nullptr);
    ~ClientRetele();

private slots:

    void on_usernameText_textChanged(const QString &arg1);

    void on_connectButton_clicked();

    void on_portText_textChanged(const QString &arg1);

    void on_serveripText_textChanged(const QString &arg1);

    void on_passwordText_textChanged(const QString &arg1);

private:
    bool connected;
    Ui::ClientRetele *ui;
    std::string address;
    std::string username;
    std::string parola;
    int port;
    std::string portHelp;
    Client *nou;
    bool canconnect;
};

#endif // CLIENTRETELE_H
