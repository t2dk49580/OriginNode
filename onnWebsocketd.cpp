#include "onnWebsocketd.h"

onnWebsocketd::onnWebsocketd():onnObject("onnWebsocketd"){

}

void onnWebsocketd::runWebsocketd(int pPort){
    initWebsocketd();
    while(!getWebsocketd()->listen(pPort)){
        std::cout << "runWebsocketd fail:" << pPort << std::endl;
        QThread::sleep(1);
        //QCoreApplication::quit();
        //exit(-1);
    }
    std::cout << "runWebsocketd ok:" << pPort << std::endl;
    getWebsocketd()->run();
}

void onnWebsocketd::onStart(){
    if(flagStart){
        return;
    }
    if(!getArgument("-ws").isEmpty()){
        std::cout << "websocketd start" << std::endl;
        QtConcurrent::run(this,&onnWebsocketd::runWebsocketd,getArgument("-ws").toInt());
        //runWebsocketd(getArgument("-ws").toInt());
    }else{
        std::cout << "websocketd stop" << std::endl;
    }
    QThread::sleep(1);
    flagStart = true;
    emit doStartFinish();
}

void onnWebsocketd::onBroadcastAppNew(QByteArray pData){
    //BUG;
    getWebsocketd()->getDefaultGroup<SERVER>().broadcast(pData,pData.count(),OpCode::TEXT);
}

void onnWebsocketd::onBroadcastAppOld(QByteArray){

}
