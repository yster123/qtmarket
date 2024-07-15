#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sqlconnect.h"

QString qusername;
QString qpassword;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qusername = ui->count->text();
    qpassword = ui->password->text();

    //跳转注册界面
    btn_reg_clicked();

    //登录
    btn_log_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_reg_clicked()
{
    connect(ui->enroll,QPushButton::clicked,[=](){
        //显示注册登录菜单
        reg=new register_window;
        this->hide();
        reg->setGeometry(this->geometry());
        reg->show();

        //监听管理员端口返回信号
        connect(reg,&register_window::sceneback,[=](){
            this->setGeometry(reg->geometry());
            this->show();
            delete reg;
            reg=NULL;

        });
    });

}

void MainWindow::btn_log_clicked()
{

    //登录（后期替换sql）
    //显示主页面
    connect(ui->login,QPushButton::clicked,[=](){
        //链接数据库
        sqlConnect *mySQL=new sqlConnect;
        QSqlDatabase db =mySQL->connect_sql();

        QSqlQuery query(db);
        QString use="use itcast;";
        query.exec(use);

        query.exec("SELECT count password FROM user");
        qusername = ui->count->text();
        qpassword = ui->password->text();


        /***********用户名和密码在数据库中判断*********/
        if (qusername == "")
        {
            QMessageBox::warning(this, "", "用户名不能为空！");
            return;
        }
        else if (qpassword == "")
        {
            QMessageBox::warning(this, "", "密码不能为空！");
            return;
        }
        else
        {
            if(ui->comboBox->currentIndex()==0)
            {
                shopping=new shoppingList;
                //判断用户名是否存在
                QString S1 = QString("select count from user where count='%1' ").arg(qusername);
                QSqlQuery query;
                query.exec(S1);//查询成功返回true，但无法确定是否存在相应信息
                if (query.first()==false)
                {
                    QMessageBox::warning(NULL, "Error", "用户名不存在！！！");
                    return;
                }
                //判断用户名所对应的密码是否存在
                QString S2 = QString("select password from user where password='%1'and count='%2' ").arg(qpassword).arg(qusername);
                QSqlQuery query2;
                query2.exec(S2);
                if (query2.first() == false)
                {
                    QMessageBox::warning(NULL, "Error", "密码错误！！！");
                }
                else if (query2.first() == true)
                {
                    QMessageBox::information(NULL, "提示", "登录成功！！！");
                    this->close();
                    shopping->show();
                    db.close();
                }
            }
            else
            {
                manager=new manager_port;
                //判断用户名是否存在
                QString S1 = QString("select count from manager where count='%1' ").arg(qusername);
                QSqlQuery query;
                query.exec(S1);//查询成功返回true，但无法确定是否存在相应信息
                if (query.first()==false)
                {
                    QMessageBox::warning(NULL, "Error", "用户名不存在！！！");
                    return;
                }
                //判断用户名所对应的密码是否存在
                QString S2 = QString("select password from manager where password='%1'and count='%2' ").arg(qpassword).arg(qusername);
                QSqlQuery query2;
                query2.exec(S2);
                if (query2.first() == false)
                {
                    QMessageBox::warning(NULL, "Error", "密码错误！！！");
                }
                else if (query2.first() == true)
                {
                    QMessageBox::information(NULL, "提示", "登录成功！！！");
                    this->close();
                    manager->show();
                    db.close();
                }

            }

        }
    });
}
