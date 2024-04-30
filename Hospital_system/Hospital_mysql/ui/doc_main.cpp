#include "doc_main.h"
#include "ui_doc_main.h"

Doc_Main::Doc_Main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doc_Main)
{
    ui->setupUi(this);
    initpage();
}

Doc_Main::~Doc_Main()
{
    delete ui;
}

void Doc_Main::initpage()
{
    m_medicine=new Medicine(this);
    m_fee=new Fee(this);
    m_recipe=new Recipe(this);
    ui->stackedWidget->addWidget(m_medicine);
    ui->stackedWidget->addWidget(m_fee);
    ui->stackedWidget->addWidget(m_recipe);
    ui->stackedWidget->setCurrentIndex(0);
    auto l=ui->tool->children();
    for(auto it:l){
        connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&Doc_Main::dealMenu);
    }
}

void Doc_Main::dealMenu()
{
    auto str=sender()->objectName();
    //qDebug()<<str;
    do{
        if(str=="medicine"){
            ui->stackedWidget->setCurrentIndex(0);
        }
        if(str=="fee"){
            ui->stackedWidget->setCurrentIndex(1);
        }
        if(str=="recipe"){
            ui->stackedWidget->setCurrentIndex(2);
        }
    }while(false);
}

void Doc_Main::on_pushButton_clicked()
{
    this->close();
}
