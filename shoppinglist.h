#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QtSql>
#include <QByteArray>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QFile>
#include <QDateTime>
#include <QListWidgetItem>
#include <QSqlField>
#include <QMetaType>
#include <QtCharts>
#include <QBarSet>

#include "sqlconnect.h"
#include "payout.h"


namespace Ui {
class shoppingList;
}

enum DateTimeType
{
    Time,
    Date,
    DateTime
};

class shoppingList : public QMainWindow
{
    Q_OBJECT

public:
    explicit shoppingList(QWidget *parent = nullptr);
    ~shoppingList();

    payout *pay;
    QChart *chart;

    void read_veget();
    void read_photo();
    void show_data();
    void set_isenterprise();
    QString getDateTime(DateTimeType type);
    void show_sellData(QSqlRecord rec);
    QSqlRecord getSellData1();
    QSqlRecord getSellData2();
    QSqlRecord getSellData3();
    QSqlRecord getSellData4();
    QSqlRecord getSellData5();
    QSqlRecord getSellData6();
    QSqlRecord getSellData7();
    QSqlRecord getSellData8();
    void set_barchart();


public:
    double sum1=0;
    double sum2=0;
    double sum3=0;
    double sum4=0;
    double sum5=0;
    double sum6=0;
    double sum7=0;
    double sum8=0;

    bool flag_1=0;
    bool flag_2=0;
    bool flag_3=0;
    bool flag_4=0;
    bool flag_5=0;
    bool flag_6=0;
    bool flag_7=0;
    bool flag_8=0;

    QSqlRecord m_record1;
    QSqlRecord m_record2;
    QSqlRecord m_record3;
    QSqlRecord m_record4;
    QSqlRecord m_record5;
    QSqlRecord m_record6;
    QSqlRecord m_record7;
    QSqlRecord m_record8;

private slots:
    void on_mainView_triggered();
    void on_actionexit_triggered();
    void on_shopCart_triggered();
    void on_selfInfo_triggered();
    void on_subComit_triggered();
    void on_sellRank_triggered();
    void on_idCert_triggered();
    void on_helpAct_triggered();
    void on_btnSave_clicked();
    void on_btnClear_clicked();
    void on_connectEnterprise_clicked();
    void on_buy1_clicked();
    void on_buy2_clicked();
    void on_buy3_clicked();
    void on_buy4_clicked();
    void on_buy5_clicked();
    void on_buy6_clicked();
    void on_buy7_clicked();
    void on_buy8_clicked();
    void on_btnClearCart_clicked();
    void on_btnCheckCart_clicked();
    void on_transShopCart_clicked();
    void on_handole_clicked();
    void on_clearThought_clicked();

//    void on_clearRec_clicked();
//    void on_btnSearch_clicked();
//    void on_showAll_clicked();
//    void paintEvent(QPaintEvent *event);


private:
    Ui::shoppingList *ui;
};

#endif // SHOPPINGLIST_H
