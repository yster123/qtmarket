#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include <QMessageBox>
#include "manager_port.h"



namespace Ui {
class manager;
}

class manager : public QWidget
{
    Q_OBJECT

public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

    manager_port *manage;

signals:
    void SceneBack();

private:
    Ui::manager *ui;
};

#endif // MANAGER_H
