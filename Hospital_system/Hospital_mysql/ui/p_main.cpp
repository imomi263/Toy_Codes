#include "p_main.h"
#include "ui_p_main.h"

P_Main::P_Main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::P_Main)
{
    ui->setupUi(this);
    initpage();
}

P_Main::~P_Main()
{
    delete ui;
}

void P_Main::initpage()
{
     m_fee=new Fee(this);
     ui->stackedWidget->addWidget(m_fee);
     ui->stackedWidget->setCurrentIndex(0);
     auto l=ui->tool->children();
     for(auto it:l){
         connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&P_Main::dealMenu);
     }
}

void P_Main::dealMenu()
{
    auto str=sender()->objectName();
    //qDebug()<<str;
    do{
        if(str=="fee"){
            ui->stackedWidget->setCurrentIndex(0);
        }

    }while(false);
}

void P_Main::on_pushButton_clicked()
{
    this->close();
}
