#include "register_window.h"
#include "ui_register_window.h"

register_window::register_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::register_window)
{
    ui->setupUi(this);

    btn_back_clicked();

    btn_reg_clicked();

}

register_window::~register_window()
{
    delete ui;
}


void register_window::btn_back_clicked()
{
    //点击返回释放信号
    connect(ui->btn_back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

}

void register_window::btn_reg_clicked()
{
    connect(ui->btn_reg,&QPushButton::clicked,[=](){
        sqlConnect *mySQL=new sqlConnect;
        QSqlDatabase db =mySQL->connect_sql();

        QSqlQuery query(db);
        QString use="use itcast;";
        query.exec(use);

        QString u = ui->count->text();
        QString p = ui->password->text();
        QString rep = ui->password_re->text();

        if(ui->comboBox->currentIndex()==0)
        {
            if (u=="")
            {
                QMessageBox::warning(NULL, "警告", "用户名不能为空！", QMessageBox::Yes);
                return;
            }
            if (p == ""||rep=="")
            {
                QMessageBox::warning(NULL, "警告", "密码或确认密码不能为空！", QMessageBox::Yes);
                return;
            }
            if (p!=rep)
            {
                QMessageBox::warning(NULL, "警告", "两次输入密码不一致！", QMessageBox::Yes);
                return;
            }
            QString S1 = QString("select count from user where count='%1' ").arg(u);
            QSqlQuery query;
            query.exec(S1);//查询成功返回true，但无法确定是否存在相应信息
            if (query.first() == true)
            {
                QMessageBox::warning(NULL, "提示", "用户名已存在！！！");
                return;
            }
            else
            {
                QString i = QString("insert into user(count,password) values ('%1','%2'); ").arg(u).arg(p);
                QSqlQuery query2;
                if (query2.exec(i))
                {
                    QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
                }
                else
                {
                    QMessageBox::warning(NULL, "Error", "注册失败，请重试！！！");
                }
            }
        }
        else
        {
            if (u=="")
            {
                QMessageBox::warning(NULL, "警告", "用户名不能为空！", QMessageBox::Yes);
                return;
            }
            if (p == ""||rep=="")
            {
                QMessageBox::warning(NULL, "警告", "密码或确认密码不能为空！", QMessageBox::Yes);
                return;
            }
            if (p!=rep)
            {
                QMessageBox::warning(NULL, "警告", "两次输入密码不一致！", QMessageBox::Yes);
                return;
            }
            QString S1 = QString("select count from manager where count='%1' ").arg(u);
            QSqlQuery query;
            query.exec(S1);//查询成功返回true，但无法确定是否存在相应信息
            if (query.first() == true)
            {
                QMessageBox::warning(NULL, "提示", "用户名已存在！！！");
                return;
            }
            else
            {
                QString i = QString("insert into manager(count,password) values ('%1','%2'); ").arg(u).arg(p);
                QSqlQuery query2;
                if (query2.exec(i))
                {
                    QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
                }
                else
                {
                    QMessageBox::warning(NULL, "Error", "注册失败，请重试！！！");
                }
            }
        }
    });

}
