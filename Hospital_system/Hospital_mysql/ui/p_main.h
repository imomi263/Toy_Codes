#ifndef P_MAIN_H
#define P_MAIN_H

#include <QWidget>
#include"fee.h"
namespace Ui {
class P_Main;
}

class P_Main : public QWidget
{
    Q_OBJECT

public:
    explicit P_Main(QWidget *parent = nullptr);
    ~P_Main();
    void initpage();
    void dealMenu();
private slots:
    void on_pushButton_clicked();

private:
    Ui::P_Main *ui;

    Fee *m_fee;

};

#endif // P_MAIN_H
