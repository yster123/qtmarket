#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma execution_character_set("utf-8")


#include "shoppinglist.h"
#include "sqlconnect.h"
#include "register_window.h"
#include "manager_port.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QtSql>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    shoppingList *shopping;
    manager_port *manager;
    sqlConnect *sql;
    register_window *reg;

    void btn_reg_clicked();
    void btn_log_clicked();

signals:
    void showweight1();
    void showweight2();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
