#include "manager_port.h"
#include "ui_manager_port.h"

manager_port::manager_port(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager_port)
{
    ui->setupUi(this);
}

manager_port::~manager_port()
{
    delete ui;
}
