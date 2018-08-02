#include "onnWebsocketd.h"

onnWebsocketd::onnWebsocketd(){

}

void onnWebsocketd::runWebsocketd(int pPort){
    if(!getWebsocketd()->listen(pPort)){
        BUG << "runWebsocketd fail:" << pPort;
        exit(-1);
    }
    getWebsocketd()->run();
}

void onnWebsocketd::onStart(){
    std::cout << "websocketd start" << std::endl;
    int curPort = 3001;
    if(!getArgument("-ws").isEmpty()){
        curPort = getArgument("-ws").toInt();
    }
    flagStart = true;
    emit doStartFinish();
    QtConcurrent::run(QThreadPool::globalInstance(),this,&onnWebsocketd::runWebsocketd,curPort);
}
