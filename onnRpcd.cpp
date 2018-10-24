#include "onnRpcd.h"

onnRpcd::onnRpcd():onnObject("onnRpcd"){

}

void onnRpcd::runRpcd(int){
//    rpc::server curRpcd(pPort);
//    curRpcd.bind("add", [&](int a, int b){
//        return a + b;
//    });
//    curRpcd.run();
}

void onnRpcd::onStart(){
    if(flagStart){
        return;
    }
    onnObject *senderObj = qobject_cast<onnObject *>(sender());
    flagStart = true;
    emit doStartFinish();
    if(!getArgument("-p").isEmpty()){
        std::cout << "rpcd start:" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
        //runHttpd(getArgument("-p").toInt());
        QtConcurrent::run(QThreadPool::globalInstance(),this,&onnRpcd::runRpcd,getArgument("-r").toInt());
    }else{
        std::cout << "rpcd stop" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
    }
}
