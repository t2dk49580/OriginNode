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
    if(!getArgument("-ws").isEmpty()){
        QtConcurrent::run(QThreadPool::globalInstance(),this,&onnWebsocketd::runWebsocketd,getArgument("-ws").toInt());
    }
    flagStart = true;
    emit doStartFinish();
}

void onnWebsocketd::onBroadcastAppNew(QByteArray pData){
    //BUG;
    getWebsocketd()->getDefaultGroup<SERVER>().broadcast(pData,pData.count(),OpCode::TEXT);
}

void onnWebsocketd::onBroadcastAppOld(QByteArray){

}
