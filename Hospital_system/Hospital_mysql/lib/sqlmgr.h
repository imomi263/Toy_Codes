#ifndef SQLMGR_H
#define SQLMGR_H

#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
class SqlMgr
{
public:
    SqlMgr();
    ~SqlMgr();
    static SqlMgr* instance;
    static SqlMgr* getInstance(){
        if(nullptr==instance){
            instance=new SqlMgr();
        }
        return instance;
    }
    void test();
    bool login();
    void init();

    QSqlDatabase m_db;

};

#endif // SQLMGR_H
