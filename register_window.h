#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H


#include "sqlconnect.h"

#include <QWidget>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QtSql>

namespace Ui {
class register_window;
}

class register_window : public QWidget
{
    Q_OBJECT

public:
    explicit register_window(QWidget *parent = nullptr);
    ~register_window();

    void btn_back_clicked();

    void btn_reg_clicked();

signals:
    sceneback();

private:
    Ui::register_window *ui;
};

#endif // REGISTER_WINDOW_H
