#ifndef DOC_MAIN_H
#define DOC_MAIN_H

#include <QWidget>
#include "medicine.h"
#include "fee.h"
#include "recipe.h"
namespace Ui {
class Doc_Main;
}

class Doc_Main : public QWidget
{
    Q_OBJECT

public:
    explicit Doc_Main(QWidget *parent = nullptr);
    ~Doc_Main();
    void initpage();
    void dealMenu();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Doc_Main *ui;
    Medicine *m_medicine;
    Fee *m_fee;
    Recipe *m_recipe;

};

#endif // DOC_MAIN_H
