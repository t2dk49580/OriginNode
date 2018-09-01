#include "onnHttpd.h"
#include <handy/handy.h>

onnHttpd::onnHttpd():onnObject("onnHttpd"){

}

void onnHttpd::runBlockNew(QByteArray pData){
    onBlockNew(pData);
}

void onnHttpd::runHttpd(int pPort){
    int threads = QThread::idealThreadCount()*2;
    handy::setloglevel("FATAL");
    handy::MultiBase base(threads);
    handy::HttpServer httpd(&base);
    int curPort = pPort;
    while(!httpd.bind("", curPort)){
        cout<<"runHttp failed:"<<curPort<<endl;
        QThread::sleep(1);
    }
    cout<<"runHttp ok:"<<curPort<<endl;
    httpd.onDefault([&](const handy::HttpConnPtr& con){
        handy::HttpResponse resp;
        QByteArray msg;
        if(con.getRequest().method == "GET"){
            msg = (con.getRequest().query_uri.c_str());
            con.clearData();
            QByteArray result = doHandlerGet(msg);
            if(!result.isEmpty()){
                resp.body = handy::Slice(result.data(),result.count());
            }else{
                resp.body = handy::Slice("null");
            }
            con.sendResponse(resp);
            con->close();
            return;
        }else if(con.getRequest().method == "POST"){
            msg = (con.getRequest().body.c_str());
            con.clearData();
            //emit doBlockNew(msg);
            QtConcurrent::run(QThreadPool::globalInstance(),this,&onnHttpd::runBlockNew,msg);
        }else{
            cout << "httpd unknow method" << con.getRequest().method << endl;
        }
        resp.body = handy::Slice(GETSHA256(msg));
        con.sendResponse(resp);
        con->close();
    });
    handy::Signal::signal(SIGINT, [&]{base.exit();});
    base.loop();
}

void onnHttpd::onStart(){
    if(flagStart){
        return;
    }
    onnObject *senderObj = qobject_cast<onnObject *>(sender());
    flagStart = true;
    emit doStartFinish();
    if(!getArgument("-p").isEmpty()){
        std::cout << "httpd start:" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
        //runHttpd(getArgument("-p").toInt());
        QtConcurrent::run(QThreadPool::globalInstance(),this,&onnHttpd::runHttpd,getArgument("-p").toInt());
    }else{
        std::cout << "httpd stop" << senderObj->objectName().toStdString() << " " << senderObj->objType.toStdString() <<std::endl;
    }
}
