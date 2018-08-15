#ifndef TEST0_H
#define TEST0_H

#include "Define.h"
#include "emcc/uECC.h"
#include "HttpRequest.h"
#include <iostream>

extern QStringList argList;

using namespace std;

class Test0 : public QObject{
    Q_OBJECT
public:
    Test0(){

    }
signals:
    void doTimeout();
    void doGet(QString,QString);
public slots:
    void onStart(){
        //emit doTimeout();
        emit doGet(argList.at(1),argList.at(2)+"$getTick$31$C7F836DC6145EA4A96A67B13EA0B5F2B10DD70544A69BCB565991F3BB5019CC7114EF777CCA2C36DEF0364D2EF733770FA72B389D3C348FDA7D98A7A7A5CF384");
    }
    void onTimeout(QString){
        if(argList.at(0).toInt()>0)
            QThread::msleep(argList.at(0).toInt());
        emit doTimeout();
        emit doGet(argList.at(1),argList.at(2)+"$getTick$31$C7F836DC6145EA4A96A67B13EA0B5F2B10DD70544A69BCB565991F3BB5019CC7114EF777CCA2C36DEF0364D2EF733770FA72B389D3C348FDA7D98A7A7A5CF384");
    }
};

#endif // TEST0_H
