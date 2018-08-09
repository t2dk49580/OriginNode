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

        HttpRequest::qtGet("http://127.0.0.1:4000/list");
        HttpRequest::qtGet("http://127.0.0.1:4000/last0");
        HttpRequest::qtGet("http://127.0.0.1:4000/block0-2");
        HttpRequest::qtGet("http://127.0.0.1:4000/peers");
        HttpRequest::qtGet("http://127.0.0.1:4000/maker0");
        HttpRequest::qtGet("http://127.0.0.1:4000/address");
        */
    }
};

#endif // TEST0_H
