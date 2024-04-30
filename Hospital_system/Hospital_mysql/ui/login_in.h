#ifndef LOGIN_IN_H
#define LOGIN_IN_H
#include "../lib/sqlmgr.h"
#include <QDialog>
#include <QSqlDatabase>
namespace Ui {
class Login_in;
}

class Login_in : public QDialog
{
    Q_OBJECT

public:
    explicit Login_in(QWidget *parent = nullptr);
    ~Login_in();

private slots:
    void on_login_clicked();

private:
    Ui::Login_in *ui;
};

#endif // LOGIN_IN_H
