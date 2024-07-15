#include "manager.h"
#include "ui_manager.h"

manager::manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);

    ui->change_u->setFlat(1);

    //点击返回用户界面释放信号
    connect(ui->change_u,&QPushButton::clicked,[=](){
        //发送返回信号
        emit SceneBack();
    });


    //登录（后期替换sql）
    //显示主页面
    manage=new manager_port;
    connect(ui->login,QPushButton::clicked,[=](){
        if(ui->count->text()=="114514" && ui->password->text()=="123456")
        {
            this->hide();
            manage->show();
        }
        else
        {
            QMessageBox::warning(this,"warning","账号或密码有误");
        }
    });

}

manager::~manager()
{
    delete ui;
}
