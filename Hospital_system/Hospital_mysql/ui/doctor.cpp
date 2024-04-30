#include "doctor.h"
#include "ui_doctor.h"

Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{

    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    m_model.setHorizontalHeaderLabels(QStringList{"Dno","Dname","Dsex","Dage","Ddeptno","Tno"});
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    titleList=QStringList{"Dno","Dname","Dsex","Dage","Ddeptno","Tno"};
    this->icols=6;
}

Doctor::~Doctor()
{
    delete ui;
}

void Doctor::on_input_clicked()
{
    m_model.clear();
    m_model.setHorizontalHeaderLabels(QStringList{"Dno","Dname","Dsex","Dage","Ddeptno","Tno"});
    qDebug()<<"医生导入";
    QSqlQuery q(SqlMgr::getInstance()->m_db);
    QString str=QString("select * from `cs2344.doctor` ");
    QVector<QStringList>vec;
    q.exec(str);
    //icols=q.record().count();
    //qDebug()<<icols<<"icols";
    while(q.next()){
        QStringList l;
        for(int i=0;i<icols;i++){

            l<<q.value(i).toString();
        }
        vec.push_back(l);
    }
    int len=vec.size();
    for(int i=0;i<len;i++){
            QList<QStandardItem*> items;
            items.append(new QStandardItem(vec[i][0]));
            items.append(new QStandardItem(vec[i][1]));
            items.append(new QStandardItem(vec[i][2]));
            items.append(new QStandardItem(vec[i][3]));
            items.append(new QStandardItem(vec[i][4]));
            items.append(new QStandardItem(vec[i][5]));

            m_model.appendRow(items);
    }

}

void Doctor::on_add_clicked()
{
    QList<QStandardItem*> items;
    ziduanList.clear();
    //qDebug()<<ziduanList.isEmpty();
    for(int i=0;i<icols;i++){
        Dialog* dia=new Dialog(this);
        dia->setAttribute(Qt::WA_DeleteOnClose,true);
        dia->setModal(true);
        QObject::connect(dia,SIGNAL(sendStr(QString)),this,SLOT(getStr(QString)));
        QObject::connect(this,SIGNAL(sendStr(QString)),dia,SLOT(getStr(QString)));
        QString str1=titleList[i];
        emit sendStr(str1);
        dia->exec();

    }
    qDebug()<<ziduanList.size();
    if(ziduanList.size()<6) return;
    QSqlQuery q(SqlMgr::getInstance()->m_db);
    QString str=QString("insert into `cs2344.doctor` values('%1','%2','%3','%4','%5','%6') ").arg(ziduanList[0]).arg(ziduanList[1])
            .arg(ziduanList[2]).arg(ziduanList[3]).arg(ziduanList[4]).arg(ziduanList[5]);
    bool ret=q.exec(str);
    if(ret){
        items.append(new QStandardItem(ziduanList[0]));
        items.append(new QStandardItem(ziduanList[1]));
        items.append(new QStandardItem(ziduanList[2]));
        items.append(new QStandardItem(ziduanList[3]));
        items.append(new QStandardItem(ziduanList[4]));
        items.append(new QStandardItem(ziduanList[5]));

        m_model.appendRow(items);
    }
    else{
        QMessageBox::warning(this,"warning","插入失败",QMessageBox::Yes);
    }
    ziduanList.clear();
}
void Doctor::getStr(QString a){
    ziduanList<<a;
}
void Doctor::on_delete_2_clicked()
{
    qDebug()<<"医生删除";
    ziduanList.clear();
    Dialog* dia=new  Dialog();
    dia->setAttribute(Qt::WA_DeleteOnClose,true);
    dia->setModal(true);
    QObject::connect(dia,SIGNAL(sendStr(QString)),this,SLOT(getStr(QString)));
    QObject::connect(this,SIGNAL(sendStr(QString)),dia,SLOT(getStr(QString)));
    QString str=titleList[0];
    emit(sendStr(str));
    dia->exec();
    if (ziduanList.isEmpty())return;
    QSqlQuery q(SqlMgr::getInstance()->m_db);
    QString str1=QString("delete  from `cs2344.doctor` where Dno='%1' ").arg(ziduanList[0]);
    bool ret= q.exec(str1);
    if(ret){
        on_input_clicked();
    }
    else{
        QSqlError error=SqlMgr::getInstance()->m_db.lastError();
        qDebug()<<error;
        QMessageBox::warning(this,"warning","删除数据失败",QMessageBox::No);
    }
    ziduanList.clear();
}

void Doctor::on_revise_clicked()
{
    qDebug()<<"医生修改";
    ziduanList.clear();

    for(int i=0;i<icols;i++){
        Dialog* dia=new Dialog(this);
        dia->setAttribute(Qt::WA_DeleteOnClose,true);
        dia->setModal(true);
        QObject::connect(dia,SIGNAL(sendStr(QString)),this,SLOT(getStr(QString)));
        QObject::connect(this,SIGNAL(sendStr(QString)),dia,SLOT(getStr(QString)));
        QString str1=titleList[i];
        emit sendStr(str1);
        dia->exec();

    }
    //qDebug()<<ziduanList.size();
    if(ziduanList.size()<8) return;
    QSqlQuery q(SqlMgr::getInstance()->m_db);
    QString str=QString(" update `cs2344.doctor` set Dname='%1',Dsex='%2',Dage='%3',Ddeptno ='%4',Tno='%5' where Dno='%6' ")
            .arg(ziduanList[1])
            .arg(ziduanList[2]).arg(ziduanList[3]).arg(ziduanList[4]).arg(ziduanList[5]).arg(ziduanList[0]);
    bool ret=q.exec(str);
    if(ret){
        on_input_clicked();
    }
    else{
        QSqlError error=q.lastError();
        qDebug()<<error.text();
        QMessageBox::warning(this,"warning","修改数据失败",QMessageBox::No);
    }
    ziduanList.clear();
}
