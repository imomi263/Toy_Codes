#ifndef FEE_H
#define FEE_H

#include <QWidget>
#include "headers.h"
namespace Ui {
class Fee;
}

class Fee : public QWidget ,public Headers
{
    Q_OBJECT

public:
    explicit Fee(QWidget *parent = nullptr);
    ~Fee();

private slots:
    void on_input_clicked();

    void on_delete_2_clicked();

    void on_add_clicked();

    void on_revise_clicked();
    void getStr(QString );
private:
    Ui::Fee *ui;
signals:
    void sendStr(QString);
};

#endif // FEE_H
