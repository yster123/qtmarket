#include "sqlconnect.h"

sqlConnect::sqlConnect(QObject *parent)
    : QObject{parent}
{

}

QSqlDatabase sqlConnect::connect_sql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("itcast");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if (ok)
    {
        qDebug()<<"连接成功";
    }
    else
    {
        qDebug()<<"error open database because"<<db.lastError().text();
    }

    QSqlQuery query;
    QString deleteTableSql = "DROP TABLE IF EXISTS vegetable";
    if (!query.exec(deleteTableSql))
    {
        qDebug() << "Error: Fail to drop ." << query.lastError();
    }

    //创建蔬菜表
    QString querystring;
    querystring = "CREATE TABLE IF NOT EXISTS vegetable "
                  "(ID INT AUTO_INCREMENT PRIMARY KEY,category varchar(20),leftNum varchar(20),picture longblob,title varchar(50),memo varchar(20),deprice int,price double,num int);";
    //执行创建数据表语句
    if(query.exec(querystring))
    {
        //插入原始数据
        QString insertSql1 = QString("INSERT INTO vegetable(id,category,leftnum,picture,title,memo,deprice,price,num) "
                                     "VALUES (1, '水果', '100',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'陕西红富士3斤','苹果',97,6.8,150),"
                                     " (2, '水果', '50',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'云南高山香蕉3斤','香蕉',98,11.8,100),"
                                     " (3, '水果', '60',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'果冻橙3斤','橘子',99,11.8,170),"
                                     " (4, '水果', '55',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'河北皇冠梨1斤','梨',98,8.8,100),"
                                     " (5, '蔬菜', '70',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'山东大白菜3斤','白菜',96,9.9,200),"
                                     " (6, '蔬菜', '50',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'水果西红柿5斤','西红柿',95,33.8,180),"
                                     " (7, '蔬菜', '55',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'现摘花菜1斤','花菜',97,6.9,80),"
                                     " (8, '蔬菜', '90',load_file('C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/DMC.jpg'),'圆茄子3斤','茄子',96,8.8,90)");
        if (!query.exec(insertSql1))
        {
            qDebug() << "Error: Fail to insert ." << query.lastError();
        }
    }
    if (db.lastError().isValid())
    {
        qDebug() << "vegetable table create failed:" << db.lastError();
        return db;
    }
    else

    //创建用户表
    querystring = "CREATE TABLE IF NOT EXISTS user "
                  "(ID INT AUTO_INCREMENT PRIMARY KEY,Count varchar(20),Password varchar(20),name varchar(20),sex varchar(1),age varchar(10),degree varchar(10),address varchar(50),signature varchar(50),headshot longblob,isenterprise int);";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "user table create failed:" << db.lastError();
        return db;
    }

    //创建管理表
    querystring = "CREATE TABLE IF NOT EXISTS manager "
                  "(ID INT AUTO_INCREMENT PRIMARY KEY,Count varchar(20),Password varchar(20));";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "manager table create failed:" << db.lastError();
        return db;
    }

    //创建企业表
    querystring = "CREATE TABLE IF NOT EXISTS enterprise "
                  "(ID INT AUTO_INCREMENT PRIMARY KEY,Count varchar(20),Password varchar(20));";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "enterprise table create failed:" << db.lastError();
        return db;
    }

    //创建出售表
    querystring = "CREATE TABLE IF NOT EXISTS sell "
                  "(ID INT AUTO_INCREMENT PRIMARY KEY,time datetime,title varchar(50),num int,price double,sum double,address varchar(50));";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "sell table create failed:" << db.lastError();
        return db;
    }

    //创建意见表
    querystring = "CREATE TABLE IF NOT EXISTS thought(ID INT AUTO_INCREMENT PRIMARY KEY,idea text);";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "sell table create failed:" << db.lastError();
        return db;
    }

    //创建帮助文档
    querystring = "CREATE TABLE IF NOT EXISTS helps(ID INT AUTO_INCREMENT PRIMARY KEY,help text);";
    db.exec(querystring);//执行创建数据表语句
    if (db.lastError().isValid())
    {
        qDebug() << "sell table create failed:" << db.lastError();
        return db;
    }

    //支持中文
    db.exec("alter table vegetable convert to character set utf8");



    return db;

}

