#pragma once
#ifndef MEDICINE_H
#define MEDICINE_H

#include <QWidget>
#include "headers.h"
namespace Ui {
class Medicine;
}

class Medicine : public QWidget ,public Headers
{
    Q_OBJECT

public:
    explicit Medicine(QWidget *parent = nullptr);
    ~Medicine();

private slots:
    void on_pushButton_clicked();

    void on_add_clicked();

    void on_delete_2_clicked();

    void on_revise_clicked();
    void getStr(QString);
private:
    Ui::Medicine *ui;

signals:
    void sendStr(QString);
};

#endif // MEDICINE_H
