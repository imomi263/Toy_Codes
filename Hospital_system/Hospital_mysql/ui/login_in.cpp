#include "login_in.h"
#include "ui_login_in.h"
#include<QMessageBox>
#include <QtDebug>
Login_in::Login_in(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_in)
{
    ui->setupUi(this);



}

Login_in::~Login_in()
{
    delete ui;
}

void Login_in::on_login_clicked()
{
    //qDebug()<<"dian le";
    QSqlQuery q(SqlMgr::getInstance()->m_db);
    QString strSql=QString("select * from `cs2344.user` where name='%1' and password='%2' ").arg(ui->name->text()).arg(ui->mima->text());
    bool ret= q.exec(strSql);


    if (q.size()==0){
        QMessageBox::warning(NULL,"waring","no match user",QMessageBox::Yes);
        setResult(0);

        hide();

    }
    else{
        QString strSql=QString("select type from `cs2344.user` where name='%1'").arg(ui->name->text());
        q.exec(strSql);
        int m=0;
        if(q.first()){
            qDebug()<<q.size();
            m=q.value(0).toInt();
            qDebug()<<q.value(0).toInt();

        }
        //if (q.value(0).toString()=='0'){
        //    hide();
        //    setResult(1);
        //}

        switch(m){
            case 0:
                    setResult(1);
                    hide();
            break;
            case 1:
                    setResult(2);
                    hide();
            break;
            case 2:
                    setResult(3);
                    hide();
            break;

        }
    }
}




