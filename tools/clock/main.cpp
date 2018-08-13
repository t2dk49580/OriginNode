#include <QCoreApplication>
#include "QTimer"
#include <Password.h>
#include "Test0.h"
#include "NetRequest.h"

QTimer *gTimer = new QTimer();
QThread *t[100] = {new QThread(),new QThread(),new QThread(),};

int main(int argc, char *argv[])
{
    if(argc<3){
        BUG << "arg1 = time step";
        BUG << "arg2 = ip";
        BUG << "arg3 = contract";
        return 0;
    }else{
        BUG << argv[1];
        BUG << argv[2];
        BUG << argv[3];
    }
    QCoreApplication a(argc, argv);
    Password *psd = new Password();
    Test0    *tt0 = new Test0();
    NetRequest *n = new NetRequest();
    psd->tgtIP = argv[2];
    psd->tgtCT = argv[3];

    psd->moveToThread(t[0]);
    tt0->moveToThread(t[1]);
    n->moveToThread(t[2]);
    QObject::connect(t[1],SIGNAL(started()),tt0,SLOT(onStart()),Qt::QueuedConnection);
    QObject::connect(t[2],SIGNAL(started()),n,SLOT(onStart()),Qt::QueuedConnection);

    int step = QString(argv[1]).toInt();
    //QObject::connect(gTimer,SIGNAL(timeout()),psd,SLOT(onTimeout()));
    //QObject::connect(gTimer,SIGNAL(timeout()),tt0,SLOT(onTimeout()));

    QObject::connect(psd,SIGNAL(doPost(QString,QString)),n,SLOT(onPost(QString,QString)),Qt::QueuedConnection);
    QObject::connect(tt0,SIGNAL(doGet(QString,QString)),n,SLOT(onGet(QString,QString)),Qt::QueuedConnection);
    QObject::connect(tt0,SIGNAL(doTimeout()),psd,SLOT(onTimeout()),Qt::QueuedConnection);

    QObject::connect(n,SIGNAL(doRsponse(QString)),tt0,SLOT(onTimeout(QString)),Qt::QueuedConnection);

    //gTimer->start(step);
    //tt0->onTimeout("");

    t[0]->start();
    t[1]->start();
    t[2]->start();
    return a.exec();
}
