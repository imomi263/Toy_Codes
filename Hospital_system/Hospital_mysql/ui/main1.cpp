#include "main1.h"
#include "ui_main1.h"
#include <QPushButton>

Main1::Main1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Main1)
    , m_patient(nullptr)
    , m_doctor(nullptr)
{
    ui->setupUi(this);
    initpage();
}

Main1::~Main1()
{
    delete ui;
}

void Main1::initpage()
{
    m_patient=new Patient(this);
    m_doctor=new Doctor(this);
    m_medicine=new Medicine(this);
    m_recipe=new Recipe(this);
    m_fee=new Fee(this);
    m_user=new User(this);
    ui->stackedWidget->addWidget(m_patient);
    ui->stackedWidget->addWidget(m_doctor);
    ui->stackedWidget->addWidget(m_medicine);
    ui->stackedWidget->addWidget(m_recipe);
    ui->stackedWidget->addWidget(m_fee);
    ui->stackedWidget->addWidget(m_user);
    ui->stackedWidget->setCurrentIndex(0);
    auto l=ui->tool->children();
    for(auto it:l){
        connect(static_cast<QPushButton*>(it),&QPushButton::clicked,this,&Main1::dealMenu);
    }
}

void Main1::dealMenu()
{

    auto str=sender()->objectName();
    //qDebug()<<str;
    do{
        if(str=="patient"){
            ui->stackedWidget->setCurrentIndex(0);
            break;
        }
        if(str=="doctor"){
            ui->stackedWidget->setCurrentIndex(1);
            break;
        }
        if(str=="medicine"){
            ui->stackedWidget->setCurrentIndex(2);
        }
        if(str=="recipe"){
            ui->stackedWidget->setCurrentIndex(3);
        }
        if(str=="fee"){
            ui->stackedWidget->setCurrentIndex(4);
        }
        if(str=="user"){
            qDebug()<<"suerrrr";
            ui->stackedWidget->setCurrentIndex(5);
        }
    }while(false);
}

void Main1::on_pushButton_clicked()
{
    this->close();
}
