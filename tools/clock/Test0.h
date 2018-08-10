#ifndef TEST0_H
#define TEST0_H

#include "Define.h"
#include "emcc/uECC.h"
#include "HttpRequest.h"

class Test0 : public QObject{
    Q_OBJECT
public:
    Test0(){

    }

public slots:
    void onTimeout(){
/*
        helpInfo.append("/help");
        helpInfo.append("/list");
        helpInfo.append("/last + 0");
        helpInfo.append("/block + 0-0");
        helpInfo.append("/peers");
        helpInfo.append("/maker + contract");
        helpInfo.append("/boss + pub");
        helpInfo.append("/balance + contract,pub");
        helpInfo.append("/address");
*/
        BUG << HttpRequest::qtGet("http://127.0.0.1:3000/TANK10$getTick$31$C7F836DC6145EA4A96A67B13EA0B5F2B10DD70544A69BCB565991F3BB5019CC7114EF777CCA2C36DEF0364D2EF733770FA72B389D3C348FDA7D98A7A7A5CF384");

    }
};

#endif // TEST0_H
