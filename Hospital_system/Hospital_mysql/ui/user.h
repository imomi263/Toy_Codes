#ifndef USER_H
#define USER_H

#include <QWidget>
#include "headers.h"

namespace Ui {
class User;
}

class User : public QWidget,public Headers
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

private:
    Ui::User *ui;
signals:
    void sendStr(QString);
private slots:
    void on_input_clicked();
    void on_delete_2_clicked();
    void on_add_clicked();
    void on_revise_clicked();
    void getStr(QString);
};

#endif // USER_H
