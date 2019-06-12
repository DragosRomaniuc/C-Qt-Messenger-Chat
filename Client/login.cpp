#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    this->close();
}

void login::on_usernameLine_textChanged(const QString &arg1)
{
    username = arg1.toStdString();
}

void login::on_passwordLine_textChanged(const QString &arg1)
{
    password = arg1.toStdString();
}
