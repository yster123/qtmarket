#ifndef MANAGER_PORT_H
#define MANAGER_PORT_H


#include <QMainWindow>

namespace Ui {
class manager_port;
}

class manager_port : public QMainWindow
{
    Q_OBJECT

public:
    explicit manager_port(QWidget *parent = nullptr);
    ~manager_port();

private:
    Ui::manager_port *ui;
};

#endif // MANAGER_PORT_H
