#include <QCoreApplication>
#include "onnSystem.h"

QTimer *timerUdpd  = new QTimer();
QTimer *timerCustom= new QTimer();

static QThread *threadChecker   = new QThread();
static QThread *threadContract  = new QThread();
static QThread *threadDatabase  = new QThread();
static QThread *threadHttpd     = new QThread();
static QThread *threadUdpd      = new QThread();
static QThread *threadWebsocketd= new QThread();

onnChecker      *blockChecker       = new onnChecker();
onnContract     *blockContract      = new onnContract();
onnDatabase     *blockDatabase      = new onnDatabase();
onnHttpd        *blockHttpd         = new onnHttpd();
onnUdpd         *blockUdpd          = new onnUdpd();
onnWebsocketd   *blockWebsocketd    = new onnWebsocketd();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int tcount = QThread::idealThreadCount()+1;
    if(tcount <= 3){
        tcount = 4;
    }

    QThreadPool::globalInstance()->setMaxThreadCount(tcount);
    onnSystem *obj = new onnSystem();

    obj->initArgv(argc,argv);
    obj->initKey();
    obj->initDatabase();
    obj->initNetSync();

    BUG << "info" << GETADDR(obj->getPubkey());
#if 0
    obj->makeBlock0();
#endif

    CONN(threadChecker,SIGNAL(started()),blockChecker,SLOT(onInit()));
    CONN(threadContract,SIGNAL(started()),blockContract,SLOT(onInit()));
    CONN(threadDatabase,SIGNAL(started()),blockDatabase,SLOT(onInit()));
    CONN(threadUdpd,SIGNAL(started()),blockUdpd,SLOT(onInit()));
    CONN(threadHttpd,SIGNAL(started()),blockHttpd,SLOT(onInit()));
    CONN(threadWebsocketd,SIGNAL(started()),blockWebsocketd,SLOT(onInit()));

    CONN(blockChecker,SIGNAL(doInitFinish()),threadContract,SLOT(start()));
    CONN(blockContract,SIGNAL(doInitFinish()),threadDatabase,SLOT(start()));
    CONN(blockDatabase,SIGNAL(doInitFinish()),threadUdpd,SLOT(start()));
    CONN(blockUdpd,SIGNAL(doInitFinish()),threadHttpd,SLOT(start()));
    CONN(blockHttpd,SIGNAL(doInitFinish()),threadWebsocketd,SLOT(start()));
    CONN(blockWebsocketd,SIGNAL(doInitFinish()),obj,SLOT(onInitFinish()));

    CONN(obj,SIGNAL(doStart()),blockDatabase,SLOT(onStart()));
    CONN(blockDatabase,SIGNAL(doStartFinish()),blockContract,SLOT(onStart()));
    CONN(blockContract,SIGNAL(doStartFinish()),blockChecker,SLOT(onStart()));
    CONN(blockChecker,SIGNAL(doStartFinish()),blockUdpd,SLOT(onStart()));
    CONN(blockUdpd,SIGNAL(doStartFinish()),blockHttpd,SLOT(onStart()));
    CONN(blockHttpd,SIGNAL(doStartFinish()),blockWebsocketd,SLOT(onStart()));
    CONN(blockWebsocketd,SIGNAL(doStartFinish()),obj,SLOT(onStartFinish()));

    blockChecker->moveToThread(threadChecker);
    blockContract->moveToThread(threadContract);
    blockDatabase->moveToThread(threadDatabase);
    blockHttpd->moveToThread(threadHttpd);
    blockUdpd->moveToThread(threadUdpd);
    blockWebsocketd->moveToThread(threadWebsocketd);

    CONN(obj,SIGNAL(doInit()),threadChecker,SLOT(start()));

    CONN(blockDatabase,SIGNAL(doBlockOld(QByteArray)),blockChecker,SLOT(onBlockOld(QByteArray)));

    CONN(blockChecker,SIGNAL(doDeployNew(QByteArray)),blockContract,SLOT(onDeployNew(QByteArray)));
    CONN(blockChecker,SIGNAL(doMethodNew(QByteArray)),blockContract,SLOT(onMethodNew(QByteArray)));
    CONN(blockChecker,SIGNAL(doPeerNew(QByteArray)),blockContract,SLOT(onPeerNew(QByteArray)));
    CONN(blockChecker,SIGNAL(doDeployOld(QByteArray)),blockContract,SLOT(onDeployOld(QByteArray)));
    CONN(blockChecker,SIGNAL(doMethodOld(QByteArray)),blockContract,SLOT(onMethodOld(QByteArray)));
    CONN(blockChecker,SIGNAL(doPeerOld(QByteArray)),blockContract,SLOT(onPeerOld(QByteArray)));
    CONN(blockChecker,SIGNAL(doDestroyNew(QByteArray)),blockContract,SLOT(onDestroyNew(QByteArray)));
    CONN(blockChecker,SIGNAL(doDestroyOld(QByteArray)),blockContract,SLOT(onDestroyOld(QByteArray)));

    CONN(blockContract,SIGNAL(doDeployNewOK(QByteArray,QByteArray)),blockDatabase,SLOT(onDeployNewOK(QByteArray,QByteArray)));
    CONN(blockContract,SIGNAL(doDeployOldOK(QByteArray,QByteArray)),blockDatabase,SLOT(onDeployOldOK(QByteArray,QByteArray)));
    CONN(blockContract,SIGNAL(doMethodNewOK(QByteArray,QByteArray)),blockDatabase,SLOT(onMethodNewOK(QByteArray,QByteArray)));
    CONN(blockContract,SIGNAL(doMethodOldOK(QByteArray,QByteArray)),blockDatabase,SLOT(onMethodOldOK(QByteArray,QByteArray)));
    CONN(blockContract,SIGNAL(doPeerNewOK(QByteArray)),blockDatabase,SLOT(onPeerNewOK(QByteArray)));
    CONN(blockContract,SIGNAL(doPeerOldOK(QByteArray)),blockDatabase,SLOT(onPeerOldOK(QByteArray)));
    CONN(blockContract,SIGNAL(doDestroyNewOK(QByteArray)),blockDatabase,SLOT(onDestroyNewOK(QByteArray)));
    CONN(blockContract,SIGNAL(doDestroyOldOK(QByteArray)),blockDatabase,SLOT(onDestroyOldOK(QByteArray)));
    CONN(blockContract,SIGNAL(doContractOldFail(QByteArray)),blockDatabase,SLOT(onContractOldFail(QByteArray)));

    CONN(blockUdpd,SIGNAL(doBlockOld(QByteArray)),blockChecker,SLOT(onBlockOld(QByteArray)));

    CONN(timerUdpd,SIGNAL(timeout()),blockUdpd,SLOT(onTimeout()));
    CONN(timerCustom,SIGNAL(timeout()),blockContract,SLOT(onTimeout()));
    CONN(blockContract,SIGNAL(timerStop()),timerCustom,SLOT(stop()));

    if(!obj->getArgument("-t").isEmpty() && !obj->getArgument("-s").isEmpty()){
        QString curContract = obj->getArgument("-t");
        QString curStep     = obj->getArgument("-s");
        if(curStep.toInt() <= 0){
            BUG << "error: -s value can not set <= 0";
            exit(-1);
        }
        blockContract->timeoutContract = curContract;
        obj->timeoutStep = curStep.toInt();
    }

    obj->init();
    timerUdpd->start(1000);
    return a.exec();
}
