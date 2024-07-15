#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

class sqlConnect : public QObject
{
    Q_OBJECT
public:
    explicit sqlConnect(QObject *parent = nullptr);

    QSqlDatabase connect_sql();

signals:

};

#endif // SQLCONNECT_H
