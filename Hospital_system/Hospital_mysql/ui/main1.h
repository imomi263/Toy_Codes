#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <QWidget>
#include "patient.h"
#include "doctor.h"
#include "medicine.h"
#include "fee.h"
#include "recipe.h"
#include "user.h"
namespace Ui {
class Main1;
}

class Main1 : public QWidget
{
    Q_OBJECT

public:
    explicit Main1(QWidget *parent = nullptr);
    ~Main1();
    void initpage();
    void dealMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Main1 *ui;
    Patient *m_patient;
    Doctor *m_doctor;
    Medicine *m_medicine;
    Fee *m_fee;
    Recipe *m_recipe;
    User *m_user;
};

#endif // MAIN_H
