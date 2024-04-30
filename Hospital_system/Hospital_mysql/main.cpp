
#include "./ui/login_in.h"
#include "./ui/main1.h"
#include "./ui/doc_main.h"
#include "./ui/p_main.h"
#include <QApplication>
#include <QDebug>
#include "./lib/sqlmgr.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlMgr::getInstance()->init();
    Login_in w;
    int ret=w.exec();
    Main1 m;
    P_Main m1;
    Doc_Main m2;
    //qDebug()<<ret;
    if(ret==1){
        //qDebug()<<"111";
        m.show();
    }
    if(ret==2){
        m1.show();
    }
    if(ret==3){
        m2.show();
    }
    return a.exec();
}
