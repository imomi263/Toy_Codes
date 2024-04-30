#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QStandardItemModel>
#include "../lib/sqlmgr.h"
#include "./dialog.h"
#include "headers.h"
namespace Ui {
class Doctor;
}

class Doctor : public QWidget , public Headers
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    ~Doctor();

private slots:
    void on_input_clicked();

    void on_add_clicked();

    void on_delete_2_clicked();
    void getStr(QString);
    void on_revise_clicked();

private:

    Ui::Doctor *ui;
    QStandardItemModel m_model;
signals:
    void sendStr(QString);
};

#endif // DOCTOR_H
