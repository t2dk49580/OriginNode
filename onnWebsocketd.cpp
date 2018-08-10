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
    flagStart = true;
    if(!getArgument("-ws").isEmpty()){
        curPort = getArgument("-ws").toInt();
        QtConcurrent::run(QThreadPool::globalInstance(),this,&onnWebsocketd::runWebsocketd,curPort);
    }
    emit doStartFinish();
}

void onnWebsocketd::onBroadcastAppNew(QByteArray){
    //BUG;
    getWebsocketd()->getDefaultGroup<SERVER>().broadcast(pData,pData.count(),OpCode::TEXT);
}

void onnWebsocketd::onBroadcastAppOld(QByteArray){

}
