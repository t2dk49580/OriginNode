#include "onnUdpd.h"

QTimer *udpTimer = new QTimer();

onnUdpd::onnUdpd(){
    CONN(udpTimer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

void onnUdpd::onStart(){
    std::cout << "onnUdpd start" << std::endl;
    flagStart = true;
    emit doStartFinish();
    udpTimer->start(1000);
}
