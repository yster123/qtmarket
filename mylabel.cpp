#include "mylabel.h"
#include "QMouseEvent"

extern QString qusername;

mylabel::mylabel(QWidget *parent)
    : QLabel{parent}
{

}

void mylabel::mousePressEvent(QMouseEvent * ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        read_photoL();
        QSqlQuery query;
        QString use="use itcast;";
        query.exec(use);

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
                this->setPixmap(pic.scaledToWidth(this->size().width()));
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
}

void mylabel::read_photoL()
{
    QString afile=QFileDialog::getOpenFileName(this,"选择图片文件","");
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
    QString updateQuery = "update user set headshot = :imageData where count = :username";
    query.prepare(updateQuery);
    query.bindValue(":imageData", data);
    query.bindValue(":username", qusername);
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
}
