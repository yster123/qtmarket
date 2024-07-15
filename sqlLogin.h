#ifndef SQLLOGIN_H
#define SQLLOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>


class sqlLogin : public QMainWindow
{
    Q_OBJECT

public:
    sqlLogin(QWidget *parent = nullptr);
    ~sqlLogin();

private:

};
#endif // SQLLOGIN_H
