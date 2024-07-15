#include "payout.h"
#include "ui_payout.h"

extern double sum;

payout::payout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::payout)
{
    ui->setupUi(this);

    //显示付款码
    QFile *file=new QFile(":/res/QRC.jpg");
    file->open(QIODevice::ReadOnly);
    QByteArray data=file->readAll();
    file->close();
    delete file;

    QPixmap pic;
    pic.loadFromData(data);
    ui->QRCode->setPixmap(pic.scaledToWidth(ui->QRCode->size().width()));

    ui->label->setText("共需支付：" + QString("%1").arg(sum) + "元");


}

payout::~payout()
{
    delete ui;
}

void payout::on_deal_clicked()
{
    emit deal();
    this->close();

}
void payout::on_exit_clicked()
{
    this->close();

}
