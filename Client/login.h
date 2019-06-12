#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    std::string username,password;

private slots:
    void on_pushButton_clicked();

    void on_usernameLine_textChanged(const QString &arg1);

    void on_passwordLine_textChanged(const QString &arg1);

private:
    Ui::login *ui;
};

#endif // LOGIN_H
