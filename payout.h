#ifndef PAYOUT_H
#define PAYOUT_H

#include <QWidget>
#include <QPixmap>
#include <QByteArray>
#include <QFile>
#include <QDebug>

namespace Ui {
class payout;
}

class payout : public QWidget
{
    Q_OBJECT

public:
    explicit payout(QWidget *parent = nullptr);
    ~payout();


private slots:
    void on_deal_clicked();
    void on_exit_clicked();

signals:
    void deal();

private:
    Ui::payout *ui;
};

#endif // PAYOUT_H
