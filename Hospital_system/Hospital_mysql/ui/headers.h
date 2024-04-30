#pragma once
#ifndef HEADERS_H
#define HEADERS_H
#include <QWidget>
#include<QStandardItem>
#endif // HEADERS_H
#include <QDebug>
#include <QSqlQuery>
#include "../lib/sqlmgr.h"
#include "dialog.h"
#include<QHeaderView>
class Headers{

public:
    QStandardItemModel m_model;
    int icols;
    QStringList ziduanList;
    QStringList titleList;



};
