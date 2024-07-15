#ifndef MYLABEL_H
#define MYLABEL_H

#include "mainwindow.h"

#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

class mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = nullptr);

    //纯虚函数的重写函数
    void mousePressEvent(QMouseEvent * ev);
    void read_photoL();

signals:

};

#endif // MYLABEL_H
