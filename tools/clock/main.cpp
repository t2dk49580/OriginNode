#include <QCoreApplication>
#include "QTimer"
#include <Password.h>
#include "Test0.h"

QTimer *gTimer = new QTimer();
QThread *t[100] = {new QThread(),new QThread(),};

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
    psd->tgtIP = argv[2];
    psd->tgtCT = argv[3];
    psd->moveToThread(t[0]);
    tt0->moveToThread(t[1]);
    t[0]->start();
    t[1]->start();
    int step = QString(argv[1]).toInt();
    QObject::connect(gTimer,SIGNAL(timeout()),psd,SLOT(onTimeout()),Qt::QueuedConnection);
    QObject::connect(gTimer,SIGNAL(timeout()),tt0,SLOT(onTimeout()),Qt::QueuedConnection);
    gTimer->start(step);
    return a.exec();
}
