#include "sqlmgr.h"
#include "../ui/login_in.h"

SqlMgr* SqlMgr::instance =nullptr;
SqlMgr::SqlMgr()
{

}

void SqlMgr::test()
{
    qDebug()<<"test";
}

bool SqlMgr::login()
{

}

void SqlMgr::init()
{
    m_db=QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("124.71.219.185");
    m_db.setDatabaseName("cs2344.his");
    m_db.setPort(3306);
    m_db.setUserName("root");
    m_db.setPassword("uestc2022!");
    bool ok=m_db.open();
    if(!ok){

        QMessageBox::warning(nullptr,"警告","打开数据库失败",QMessageBox::Yes);
        //qDebug()<<ip;
    }
    else{
        qDebug()<<"chenggongle";
    }
}
