#include "onnSystem.h"

extern onnChecker      *blockChecker;
extern onnContract     *blockContract;
extern onnDatabase     *blockDatabase;
extern onnHttpd        *blockHttpd;
extern onnUdpd         *blockUdpd;
extern onnWebsocketd   *blockWebsocketd;

extern QTimer *timerCustom;

onnSystem::onnSystem():onnObject("onnSystem"){

}

void onnSystem::initBoss(){
    setBoss("0","b76883e450099de14ed93c348935b7c506f60a39");
}

void onnSystem::onInitFinish(){
    emit doStart();
}

void onnSystem::onStartFinish(){
    if(!getReadableContract().isEmpty()){
        BUG << "fatal error: getReadableContract() != null";
        exit(-1);
    }else{
        BUG << "ok";
    }
    CONN(blockHttpd,SIGNAL(doBlockNew(QByteArray)),blockChecker,SLOT(onBlockNew(QByteArray)));

    if(!getArgument("-ws").isEmpty()){
        CONN(blockContract,SIGNAL(doBroadcastAppNew(QByteArray)),blockWebsocketd,SLOT(onBroadcastAppNew(QByteArray)));
    }
    //CONN(blockContract,SIGNAL(doSendBlockChainData(QString,QString,QString)),getNetSync(),SLOT(onSendBlockChainData(QString,QString,QString)));
    CONN(blockContract,SIGNAL(doSetBossList(QByteArrayList)),getNetSync(),SLOT(onGetBossAddr(QByteArrayList)));
    CONN(blockContract,SIGNAL(doCustomBroadcast(QString,QString,QString)),getNetSync(),SLOT(onOnnBroadcast(QString,QString,QString)));
    CONN(blockContract,SIGNAL(doCustomRequire(QString,QByteArray,QString,QString)),getNetSync(),SLOT(onOnnRequire(QString,QByteArray,QString,QString)));

    //CONN(blockUdpd,SIGNAL(doBroadcastBlockChainLevel(QString,QString)),getNetSync(),SLOT(onBroadcastBlockChainLevel(QString,QString)));
    //CONN(blockUdpd,SIGNAL(doRequireBlockChainData(QString,QString,QString,QString)),getNetSync(),SLOT(onRequireBlockChainData(QString,QString,QString,QString)));
    //CONN(blockUdpd,SIGNAL(doSendBlockChainData(QString,QString,QString)),getNetSync(),SLOT(onSendBlockChainData(QString,QString,QString)));
    CONN(blockUdpd,SIGNAL(doSetBossList(QByteArrayList)),getNetSync(),SLOT(onGetBossAddr(QByteArrayList)));
    CONN(blockUdpd,SIGNAL(doCustomBroadcast(QString,QString,QString)),getNetSync(),SLOT(onOnnBroadcast(QString,QString,QString)));
    CONN(blockUdpd,SIGNAL(doCustomRequire(QString,QByteArray,QString,QString)),getNetSync(),SLOT(onOnnRequire(QString,QByteArray,QString,QString)));
    CONN(blockUdpd,SIGNAL(doBlockNew(QByteArray)),blockChecker,SLOT(onBlockNew(QByteArray)));

    //CONN(getNetSync(),SIGNAL(doRcvBlockChainData(QString,QString,QString)),blockUdpd,SLOT(onSendBlockChainData(QString,QString,QString)));
    //CONN(getNetSync(),SIGNAL(doRcvBlockChainDataRequire(QString,QString,QString,QString)),blockUdpd,SLOT(onRequireBlockChainData(QString,QString,QString,QString)));
    //CONN(getNetSync(),SIGNAL(doRcvBlockChainLevel(QString,QString,QString)),blockUdpd,SLOT(onBroadcastBlockChainLevel(QString,QString,QString)));
    CONN(getNetSync(),SIGNAL(doUpdatePeerList(QStringList,QStringList,QStringList)),blockUdpd,SLOT(onUdpdPeer(QStringList,QStringList,QStringList)));
    CONN(getNetSync(),SIGNAL(doOnnRequire(QString,QString,QString,QString)),blockUdpd,SLOT(onCustomRequire(QString,QString,QString,QString)));
    /*concurrent*/
    CONN(blockUdpd,SIGNAL(doDeployNew(QByteArray)),blockContract,SLOT(onDeployNew(QByteArray)));
    CONN(blockUdpd,SIGNAL(doMethodNew(QByteArray)),blockContract,SLOT(onMethodNew(QByteArray)));
    CONN(blockUdpd,SIGNAL(doPeerNew(QByteArray)),blockContract,SLOT(onPeerNew(QByteArray)));
    CONN(blockHttpd,SIGNAL(doDeployNew(QByteArray)),blockContract,SLOT(onDeployNew(QByteArray)));
    CONN(blockHttpd,SIGNAL(doMethodNew(QByteArray)),blockContract,SLOT(onMethodNew(QByteArray)));
    CONN(blockHttpd,SIGNAL(doPeerNew(QByteArray)),blockContract,SLOT(onPeerNew(QByteArray)));

    if(!getArgument("-t").isEmpty() && !getArgument("-s").isEmpty()){
        timerCustom->start(timeoutStep);
    }
}
