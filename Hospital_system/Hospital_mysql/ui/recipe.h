#ifndef RECIPE_H
#define RECIPE_H

#include <QWidget>
#include "headers.h"
namespace Ui {
class Recipe;
}

class Recipe : public QWidget,public Headers
{
    Q_OBJECT

public:
    explicit Recipe(QWidget *parent = nullptr);
    ~Recipe();

private:
    Ui::Recipe *ui;
signals:
    void sendStr(QString);
private slots:
    void on_input_clicked();
    void on_delete_2_clicked();
    void on_add_clicked();
    void on_revise_clicked();
    void getStr(QString);
};

#endif // RECIPE_H
