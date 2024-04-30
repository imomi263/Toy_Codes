#pragma once
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//这是管理病人的窗口
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


    Ui::Dialog *ui;
signals:
    void sendStr(QString);
private slots:
    void on_pushButton_clicked();
    void getStr(QString);
};

#endif // DIALOG_H
