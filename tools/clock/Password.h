#ifndef PASSWORD_H
#define PASSWORD_H

#include "Define.h"
#include "emcc/uECC.h"
#include "HttpRequest.h"

class Password : public QObject{
    Q_OBJECT
public:
    Password(){
        passwdFile = "config.ini";
        setting = new QSettings(passwdFile,QSettings::IniFormat);
        if(hasAppkey()){
            appkey = setting->value("appkey").toString().toLatin1();
        }
        if(hasPubkey()){
            pubkey = setting->value("pubkey").toString().toLatin1();
            prikey = setting->value("prikey").toString().toLatin1();
        }else{
            makeKey();
        }
    }
    ~Password(){}

    bool hasAppkey(){
        if (!setting->contains("appkey")){
            return false;
        }
        return true;
    }

    void updAppkey(QByteArray pKey){
        appkey = pKey;
        setting->setValue("appkey",appkey);
    }

    bool hasPubkey(){
        if (!setting->contains("pubkey")){
            return false;
        }
        return true;
    }

    void makeKey(){
        getkey();
        pubkey = getPublicKey();
        prikey = getPrivateKey();
        prikey = prikey.left(64);   //need use AES

        setting->setValue("pubkey",pubkey);
        setting->setValue("prikey",prikey);
    }

    QString tgtIP;
    QString tgtCT;
    QString passwdFile;
    QByteArray pubkey;
    QByteArray prikey;
    QByteArray appkey;
    QByteArray signmsg;
    QSettings *setting;

public slots:
    void onTimeout(){
        HttpRequest::doMethodSet(prikey,pubkey,QString("http://")+tgtIP,tgtCT,"timeout","null");
    }
};


#endif // PASSWORD_H
