#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>
#include <QStandardItemModel>
#include "../lib/sqlmgr.h"
#include "./dialog.h"

namespace Ui {
class Patient;
}

class Patient : public QWidget
{
    Q_OBJECT

public:
    explicit Patient(QWidget *parent = nullptr);
    ~Patient();

private slots:
    void on_pushButton_clicked();

    void on_add_clicked();
    void getStr(QString);
    void on_delete_2_clicked();

    void on_revise_clicked();

private:
    Ui::Patient *ui;
    QStandardItemModel m_model;
    const int icols=8;
    QStringList ziduanList;
    QStringList titleList={"Pno","Pname","Pid","Pino","Pmno","Psex","Pbd","Padd"};
signals:
    void sendStr(QString);
};

#endif // PATIENT_H
