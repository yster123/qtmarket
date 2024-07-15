#include "shoppinglist.h"
#include "ui_shoppinglist.h"

extern QString qusername;

using namespace std;

double sum;

shoppingList::shoppingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shoppingList)
{
    ui->setupUi(this);

    //链接数据库
    sqlConnect *mySQL=new sqlConnect;
    QSqlDatabase db =mySQL->connect_sql();

    //设置默认界面
    ui->stackedWidget->setCurrentIndex(2);

    QMessageBox::information(this,"请先提交个人信息后再进行购物","请先提交个人信息后再进行购物");

    read_veget();

    show_data();

    set_barchart();

    sum=sum1+sum2+sum3+sum3+sum4+sum5+sum6+sum7+sum8;
}

shoppingList::~shoppingList()
{
    delete ui;
}

//读取商品数据
void shoppingList::read_veget()
{
    QSqlQuery query;
    query.exec("SELECT * FROM vegetable");
    int i=1;
    while (query.next())
    {
        QLabel *labelPic;
        QLabel *labeltitle;
        QLabel *labelmemo;
        QLabel *labelevent;
        QLabel *labelprice;
        switch (i)
        {
        case 1:
            labelPic = ui->pic_1;
            labeltitle=ui->title_1;
            labelmemo=ui->memo_1;
            labelevent=ui->event_1;
            labelprice=ui->price_1;
            break;
        case 2:
            labelPic = ui->pic_2;
            labeltitle=ui->title_2;
            labelmemo=ui->memo_2;
            labelevent=ui->event_2;
            labelprice=ui->price_2;
            break;
        case 3:
            labelPic = ui->pic_3;
            labeltitle=ui->title_3;
            labelmemo=ui->memo_3;
            labelevent=ui->event_3;
            labelprice=ui->price_3;
            break;
        case 4:
            labelPic = ui->pic_4;
            labeltitle=ui->title_4;
            labelmemo=ui->memo_4;
            labelevent=ui->event_4;
            labelprice=ui->price_4;
            break;
        case 5:
            labelPic = ui->pic_5;
            labeltitle=ui->title_5;
            labelmemo=ui->memo_5;
            labelevent=ui->event_5;
            labelprice=ui->price_5;
            break;
        case 6:
            labelPic = ui->pic_6;
            labeltitle=ui->title_6;
            labelmemo=ui->memo_6;
            labelevent=ui->event_6;
            labelprice=ui->price_6;
            break;
        case 7:
            labelPic = ui->pic_7;
            labeltitle=ui->title_7;
            labelmemo=ui->memo_7;
            labelevent=ui->event_7;
            labelprice=ui->price_7;
            break;
        case 8:
            labelPic = ui->pic_8;
            labeltitle=ui->title_8;
            labelmemo=ui->memo_8;
            labelevent=ui->event_8;
            labelprice=ui->price_8;
            break;
        }
        if(labelPic)
        {
            QVariant va=query.value(3).toByteArray();
            if(!va.isValid())
            {
                labelPic->clear();
            }
            else
            {
                QByteArray data=va.toByteArray();
                QPixmap pic;
                pic.loadFromData(data);
                labelPic->setPixmap(pic.scaledToWidth(labelPic->size().width()));
            }
        }

        labeltitle->setText(query.value(4).toString());
        labelmemo->setText(query.value(5).toString());
        labelevent->setText(query.value(6).toString()+"折");
        labelprice->setText(query.value(7).toString()+"元");
        i++;
    }
}

void shoppingList::read_photo()
{
    QString afile=QFileDialog::getOpenFileName(this,"选择图片文件","","照片(*.jpg)");
    if(afile.isEmpty())
    {
        QMessageBox::warning(this,"读取失败","读取失败");
        return;
    }
    QByteArray data;
    QFile *file=new QFile(afile);
    file->open(QIODevice::ReadOnly);
    data=file->readAll();
    file->close();
    delete file;

    QSqlQuery query;
    QString S1=QString("update user set headshot=%1 where count=%2;").arg(data).arg(qusername);
    if(!query.exec(S1))
    {
        qDebug()<<query.lastError();

    }

}

void shoppingList::show_data()
{
    QSqlQuery query;
    query.prepare("select name,sex,age,degree,address,signature from user where count=:count");
    query.bindValue(":count",  qusername);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        ui->name->setText(query.value(0).toString());
        ui->sex->setText(query.value(1).toString());
        ui->age->setText(query.value(2).toString());
        ui->degree->setText(query.value(3).toString());
        ui->address->setText(query.value(4).toString());
        ui->signature->setText(query.value(5).toString());
        QString S1 = QString("select headshot from user where count = %1").arg(qusername);
        if (!query.exec(S1))
        {
            qDebug() << "Error: Fail to execute query." << query.lastError();
        }
        if (query.next())
        {
            QVariant va = query.value(0);
            if (va.isValid())
            {
                QByteArray data=va.toByteArray();
                QPixmap pic;
                pic.loadFromData(data);
                ui->headshot->setPixmap(pic.scaledToWidth(ui->headshot->size().width()));
            }
            else
            {
                qDebug() << "Error: Invalid data retrieved from the database.";
            }
        }
        else
        {
            qDebug() << "Error: No data found in the database.";
        }
    }

    //修改帮助文档
    QSqlQuery query2;
    query2.exec("select help from helps;");
    if(query2.next())
        ui->helpText->setText(query2.value(0).toString());
}


QString shoppingList::getDateTime(DateTimeType type)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm");
    QString dateAndTime = datetime.toString("yyyy-MM-dd dddd hh:mm");

    if(type == Date)
    {
        return date;
    }
    else if(type == Time)
    {
        return time;
    }
    else
    {
        return dateAndTime;
    }
}


void shoppingList::on_btnSave_clicked()
{
    QString m_name=ui->name->text();
    QString m_sex=ui->sex->text();
    QString m_age=ui->age->text();
    QString m_degree=ui->degree->text();
    QString m_address=ui->address->text();
    QString m_signature=ui->signature->text();

    QSqlQuery query;
    query.prepare("update user set name=:name, sex=:sex, age=:age, degree=:degree, address=:address, signature=:signature where count=:count");
    query.bindValue(":name",  m_name);
    query.bindValue(":sex",  m_sex);
    query.bindValue(":age",  m_age);
    query.bindValue(":degree",  m_degree);
    query.bindValue(":address",  m_address);
    query.bindValue(":signature",  m_signature);
    query.bindValue(":count",  qusername);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    else
    {
        QMessageBox::information(this,"保存成功","保存成功");
        ui->stackedWidget->setCurrentIndex(0);
    }

}

void shoppingList::on_btnClear_clicked()
{
   ui->name->clear();
   ui->sex->clear();
   ui->age->clear();
   ui->degree->clear();
   ui->address->clear();
   ui->signature->clear();
   ui->headshot->clear();
}

void shoppingList::on_mainView_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void shoppingList::on_shopCart_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void shoppingList::on_selfInfo_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void shoppingList::on_idCert_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void shoppingList::on_sellRank_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);

}

void shoppingList::on_subComit_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void shoppingList::on_helpAct_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);

}

void shoppingList::on_actionexit_triggered()
{
    this->close();

}

void shoppingList::on_connectEnterprise_clicked()
{
    QString enterpriseName = ui->userIsentprise->text();
    QString enterprisePassword = ui->passwordIsenterprise->text();

    QSqlQuery query;

    if (enterpriseName == "")
    {
        QMessageBox::warning(this, "", "用户名不能为空！");
        return;
    }
    else if (enterprisePassword == "")
    {
        QMessageBox::warning(this, "", "密码不能为空！");
        return;
    }
    else
    {
        //判断用户名是否存在
        QString S1 = QString("select count from enterprise where count='%1' ").arg(enterpriseName);
        QSqlQuery query;
        query.exec(S1);//查询成功返回true，但无法确定是否存在相应信息
        if (query.first()==false)
        {
            QMessageBox::warning(NULL, "Error", "用户名不存在！！！");
            return;
        }
        //判断用户名所对应的密码是否存在
        QString S2 = QString("select password from enterprise where password='%1'and count='%2' ").arg(enterprisePassword).arg(enterpriseName);
        QSqlQuery query2;
        query2.exec(S2);
        if (query2.first() == false)
        {
            QMessageBox::warning(NULL, "Error", "密码错误！！！");
        }
        else if (query2.first() == true)
        {
            QString S3 =QString("update user set isenterprise = 1 where count=%1").arg(qusername);
            query.exec(S3);
            QMessageBox::information(NULL, "提示", "关联企业成功！！！");
        }
    }

}

void shoppingList::show_sellData(QSqlRecord rec)
{
    QString currentDateTime = getDateTime(DateTime);

    QListWidgetItem *titleItem = new QListWidgetItem;
    titleItem ->setText(QString("--------%1--------").arg(rec.value("time1").toString()));
    titleItem ->setTextAlignment(Qt::AlignCenter);
    ui ->shoppingCart->addItem(titleItem);

    QString str = QString( currentDateTime + "添加" + rec.value("title1").toString() + " "+ rec.value("num1").toString() + "单，" + "单价:" + rec.value("price1").toString() + "，共" + "%1元").arg(rec.value("sum1").toDouble());
    QListWidgetItem *tempItem = new QListWidgetItem;
    tempItem ->setText("******************************");
    tempItem ->setTextAlignment(Qt::AlignCenter);
    ui ->shoppingCart ->addItem(tempItem);
    ui ->shoppingCart ->addItem(str);

    QMessageBox::information(this,"购物车","添加成功");
}

QSqlRecord shoppingList::getSellData1()
{
    QSqlRecord rec;
    QString title=QString(ui->title_1->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_1->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            //修改数字精度
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum1 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum1 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum1);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}

QSqlRecord shoppingList::getSellData2()
{
    QSqlRecord rec;
    QString title=QString(ui->title_2->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_2->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum2 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum2 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum2);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData3()
{
    QSqlRecord rec;
    QString title=QString(ui->title_3->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_3->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum3 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum3 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum3);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData4()
{
    QSqlRecord rec;
    QString title=QString(ui->title_4->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_4->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum4 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum4 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum4);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData5()
{
    QSqlRecord rec;
    QString title=QString(ui->title_5->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_5->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum5 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum5 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum5);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData6()
{
    QSqlRecord rec;
    QString title=QString(ui->title_6->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_6->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum6 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum6 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum6);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData7()
{
    QSqlRecord rec;
    QString title=QString(ui->title_7->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_7->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum7 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum7 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum7);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}
QSqlRecord shoppingList::getSellData8()
{
    QSqlRecord rec;
    QString title=QString(ui->title_8->text());
    qDebug() << title;
    QSqlQuery query;
    query.prepare("select price,deprice from vegetable where title=:title");
    query.bindValue(":title",  title);
    if(!query.exec())
    {
        QMessageBox::warning(this,"错误",query.lastError().text());
    }
    if(query.next())
    {
        QSqlQuery query2;
        query2.prepare("select isenterprise from user where count=:count");
        query2.bindValue(":count",  qusername);
        if(!query2.exec())
        {
            QMessageBox::warning(this,"错误",query.lastError().text());
        }
        if(query2.next())
        {
            bool isEnterprise = query2.value(0).toBool();
            int num=ui->num_8->text().toInt();
            double price=query.value(0).toDouble();
            int deprice=query.value(1).toInt();
            if(isEnterprise)
            {
                double rec_s=price*num*deprice*0.01*0.97;
                sum8 = QString::number(rec_s, 'f', 1).toDouble();
            }
            else
            {
                double rec_s=price*num*deprice*0.01;
                sum8 = QString::number(rec_s, 'f', 1).toDouble();
            }
            QString currentDate = getDateTime(Date);

            QSqlField field1("time1", QVariant::String);
            field1.setValue(currentDate);
            rec.append(field1);

            QSqlField field2("title1", QVariant::String);
            field2.setValue(title);
            rec.append(field2);

            QSqlField field3("num1", QVariant::Int);
            field3.setValue(num);
            rec.append(field3);

            QSqlField field4("price1", QVariant::Double);
            field4.setValue(price);
            rec.append(field4);

            QSqlField field5("sum1", QVariant::Double);
            field5.setValue(sum8);
            rec.append(field5);


            QSqlField field6("address1", QVariant::String);
            field6.setValue(ui->address->text());
            rec.append(field6);

            qDebug() << rec.value("title").toString();
        }

    }
    return rec;
}



//使用引用来修改全局变量
void shoppingList::on_buy1_clicked()
{
    m_record1=getSellData1();
    show_sellData(m_record1);
    flag_1=1;
    ui->buy1->setEnabled(0);
}

void shoppingList::on_buy2_clicked()
{
    m_record2=getSellData2();
    show_sellData(m_record2);
    flag_2=1;
    ui->buy2->setEnabled(0);
}

void shoppingList::on_buy3_clicked()
{
    m_record3=getSellData3();
    show_sellData(m_record3);
    flag_3=1;
    ui->buy3->setEnabled(0);
}

void shoppingList::on_buy4_clicked()
{
    m_record4=getSellData4();
    show_sellData(m_record4);
    flag_4=1;
    ui->buy4->setEnabled(0);
}

void shoppingList::on_buy5_clicked()
{
    m_record5=getSellData5();
    show_sellData(m_record5);
    flag_5=1;
    ui->buy5->setEnabled(0);
}

void shoppingList::on_buy6_clicked()
{
    m_record6=getSellData6();
    show_sellData(m_record6);
    flag_6=1;
    ui->buy6->setEnabled(0);
}

void shoppingList::on_buy7_clicked()
{
    m_record7=getSellData7();
    show_sellData(m_record7);
    flag_7=1;
    ui->buy7->setEnabled(0);
}

void shoppingList::on_buy8_clicked()
{
    m_record8=getSellData8();
    show_sellData(m_record8);
    flag_8=1;
    ui->buy8->setEnabled(0);
}

void shoppingList::on_btnCheckCart_clicked()
{
    sum=sum1+sum2+sum3+sum4+sum5+sum6+sum7+sum8;
    if(sum==0)
    {
        QMessageBox::information(this,"购物车","没有需要结算的物品");
        return;
    }
    pay=new payout;
    pay->show();

    connect(pay,&payout::deal,[=](){

        QSqlQuery query;
        query.exec("use itcast");

        if(flag_1==1)
        {
            flag_1=0;

            //设置字符串转double精度
            QString sumStr1 = QString::number(m_record1.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record1.value("time1"));
            query.bindValue(":title",  m_record1.value("title1"));
            query.bindValue(":num",  m_record1.value("num1"));
            query.bindValue(":price",  m_record1.value("price1"));
            query.bindValue(":sum",  sumStr1);
            query.bindValue(":address",  m_record1.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record1.value("num1").toInt());
            query2.bindValue(":title",  m_record1.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record1.clear();
        }

        if(flag_2==1)
        {
            flag_2=0;

            //设置字符串转double精度
            QString sumStr2 = QString::number(m_record2.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record2.value("time1"));
            query.bindValue(":title",  m_record2.value("title1"));
            query.bindValue(":num",  m_record2.value("num1"));
            query.bindValue(":price",  m_record2.value("price1"));
            query.bindValue(":sum",  sumStr2);
            query.bindValue(":address",  m_record2.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record2.value("num1").toInt());
            query2.bindValue(":title",  m_record2.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record2.clear();
        }

        if(flag_3==1)
        {
            flag_3=0;

            //设置字符串转double精度
            QString sumStr3 = QString::number(m_record3.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            //更新数据库sell表的数据
            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record3.value("time1"));
            query.bindValue(":title",  m_record3.value("title1"));
            query.bindValue(":num",  m_record3.value("num1"));
            query.bindValue(":price",  m_record3.value("price1"));
            query.bindValue(":sum",  sumStr3);
            query.bindValue(":address",  m_record3.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record3.value("num1").toInt());
            query2.bindValue(":title",  m_record3.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record3.clear();
        }

        if(flag_4==1)
        {
            flag_4=0;

            //设置字符串转double精度
            QString sumStr4 = QString::number(m_record4.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record4.value("time1"));
            query.bindValue(":title",  m_record4.value("title1"));
            query.bindValue(":num",  m_record4.value("num1"));
            query.bindValue(":price",  m_record4.value("price1"));
            query.bindValue(":sum",  sumStr4);
            query.bindValue(":address",  m_record4.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record4.value("num1").toInt());
            query2.bindValue(":title",  m_record4.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record4.clear();
        }

        if(flag_5==1)
        {
            flag_5=0;

            //设置字符串转double精度
            QString sumStr5 = QString::number(m_record5.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record5.value("time1"));
            query.bindValue(":title",  m_record5.value("title1"));
            query.bindValue(":num",  m_record5.value("num1"));
            query.bindValue(":price",  m_record5.value("price1"));
            query.bindValue(":sum",  sumStr5);
            query.bindValue(":address",  m_record5.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record5.value("num1").toInt());
            query2.bindValue(":title",  m_record5.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record5.clear();
        }

        if(flag_6==1)
        {
            flag_6=0;

            //设置字符串转double精度
            QString sumStr6 = QString::number(m_record6.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record6.value("time1"));
            query.bindValue(":title",  m_record6.value("title1"));
            query.bindValue(":num",  m_record6.value("num1"));
            query.bindValue(":price",  m_record6.value("price1"));
            query.bindValue(":sum",  sumStr6);
            query.bindValue(":address",  m_record6.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record6.value("num1").toInt());
            query2.bindValue(":title",  m_record6.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");
            m_record6.clear();
        }

        if(flag_7==1)
        {
            flag_7=0;

            //设置字符串转double精度
            QString sumStr7 = QString::number(m_record7.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record7.value("time1"));
            query.bindValue(":title",  m_record7.value("title1"));
            query.bindValue(":num",  m_record7.value("num1"));
            query.bindValue(":price",  m_record7.value("price1"));
            query.bindValue(":sum",  sumStr7);
            query.bindValue(":address",  m_record7.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record7.value("num1").toInt());
            query2.bindValue(":title",  m_record7.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");

            m_record7.clear();
        }

        if(flag_8==1)
        {
            flag_8=0;

            //设置字符串转double精度
            QString sumStr8 = QString::number(m_record8.value("sum1").toDouble(), 'f', 2); // 转换为字符串，保留两位小数

            QSqlQuery query;
            query.prepare("insert into sell (time, title, num, price, sum, address) values (:time, :title, :num, :price, :sum, :address);");
            query.bindValue(":time",  m_record8.value("time1"));
            query.bindValue(":title",  m_record8.value("title1"));
            query.bindValue(":num",  m_record8.value("num1"));
            query.bindValue(":price",  m_record8.value("price1"));
            query.bindValue(":sum",  sumStr8);
            query.bindValue(":address",  m_record8.value("address1"));
            if(!query.exec())
                QMessageBox::warning(this,"购物车","结算失败");

            //更新数据库vegetable表的数据
            QSqlQuery query2;
            query2.prepare("update vegetable set num=num + :num1 , leftnum=leftnum - :num1 where title=:title");
            query2.bindValue(":num1",  m_record8.value("num1").toInt());
            query2.bindValue(":title",  m_record8.value("title1").toString());
            if(!query2.exec())
                QMessageBox::warning(this,"购物车","扣除失败");
            m_record8.clear();
        }
        ui->shoppingCart->clear();
        QMessageBox::information(this,"支付","支付成功！");
        chart->removeAllSeries();
        chart->close();
        set_barchart();
        ui->num_1->clear();
        ui->num_2->clear();
        ui->num_3->clear();
        ui->num_4->clear();
        ui->num_5->clear();
        ui->num_6->clear();
        ui->num_7->clear();
        ui->num_8->clear();
        m_record1.clear();
        sum1=0;
        m_record2.clear();
        sum2=0;
        m_record3.clear();
        sum3=0;
        m_record4.clear();
        sum4=0;
        m_record5.clear();
        sum5=0;
        m_record6.clear();
        sum6=0;
        m_record7.clear();
        sum7=0;
        m_record8.clear();
        sum8=0;
        ui->buy1->setEnabled(1);
        ui->buy2->setEnabled(1);
        ui->buy3->setEnabled(1);
        ui->buy4->setEnabled(1);
        ui->buy5->setEnabled(1);
        ui->buy6->setEnabled(1);
        ui->buy7->setEnabled(1);
        ui->buy8->setEnabled(1);
    });
}

void shoppingList::on_btnClearCart_clicked()
{
    ui->num_1->clear();
    ui->num_2->clear();
    ui->num_3->clear();
    ui->num_4->clear();
    ui->num_5->clear();
    ui->num_6->clear();
    ui->num_7->clear();
    ui->num_8->clear();
    m_record1.clear();
    sum1=0;
    m_record2.clear();
    sum2=0;
    m_record3.clear();
    sum3=0;
    m_record4.clear();
    sum4=0;
    m_record5.clear();
    sum5=0;
    m_record6.clear();
    sum6=0;
    m_record7.clear();
    sum7=0;
    m_record8.clear();
    sum8=0;
    ui->buy1->setEnabled(1);
    ui->buy2->setEnabled(1);
    ui->buy3->setEnabled(1);
    ui->buy4->setEnabled(1);
    ui->buy5->setEnabled(1);
    ui->buy6->setEnabled(1);
    ui->buy7->setEnabled(1);
    ui->buy8->setEnabled(1);
    ui->shoppingCart->clear();
    QMessageBox::information(this,"购物车","购物车清空成功");
}

void shoppingList::on_transShopCart_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void shoppingList::on_handole_clicked()
{
    QString textIn=ui->thoughtBack->text();

    QSqlQuery query;
    query.prepare("insert into thought (idea) values (:text)");
    query.bindValue(":text",  textIn);
    if(!query.exec())
        QMessageBox::warning(this,"错误","数据插入错误");
    else
    {
        QMessageBox::information(this,"意见","意见提交成功");
        ui->thoughtBack->clear();
    }
}

void shoppingList::on_clearThought_clicked()
{
    ui->thoughtBack->clear();
}

void shoppingList::set_barchart()
{
    int i=0;
    int num_1=0;
    int num_2=0;
    int num_3=0;
    int num_4=0;
    int num_5=0;
    int num_6=0;
    int num_7=0;
    int num_8=0;
    // 创建一个类别轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QSqlQuery query;
    query.exec("select num,memo from vegetable");
    while(query.next())
    {
        i++;
        switch(i)
        {
        case 1:
            num_1=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 2:
            num_2=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 3:
            num_3=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 4:
            num_4=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 5:
            num_5=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 6:
            num_6=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 7:
            num_7=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        case 8:
            num_8=query.value(0).toInt();
            axisX->append(query.value(1).toString());
            break;
        }
    }

    // 创建一个柱状图系列
    QBarSeries *series = new QBarSeries();

    // 添加柱状图数据
    QBarSet *set0 = new QBarSet("/单");
    *set0 << num_1 << num_2 << num_3 << num_4 << num_5 << num_6 << num_7 << num_8; // 设置柱状图数据
    series->append(set0); // 将数据添加到系列中

    // 创建柱状图
    chart = new QChart();
    chart->addSeries(series); // 将系列添加到柱状图中
    chart->setTitle("产品销量统计图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes(); // 创建默认的轴
    chart->setAxisX(axisX, series); // 设置X轴

    // 创建柱状图视图
    QChartView *barView = new QChartView(chart, ui->stackedWidget->widget(4));
    barView->setGeometry(0, 0, 782, 575);

}
