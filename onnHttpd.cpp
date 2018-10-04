#include "onnHttpd.h"
#include <handy/handy.h>

extern onnHttpd        *blockHttpd;

onnHttpd::onnHttpd():onnObject("onnHttpd"){
    port = 3000;
}

void onnHttpd::runBlockNew(QByteArray pData){
    onBlockNew(pData);
}

//void onnHttpd::runHttpd(int pPort){
//    blockHttpd->port = pPort;
//    std::vector<std::thread *> threads(QThreadPool::globalInstance()->maxThreadCount());
//    std::transform(threads.begin(), threads.end(), threads.begin(), [](std::thread *t) {
//        return new std::thread([]() {
//            uWS::Hub h;

//            h.onHttpRequest([&](HttpResponse *res, HttpRequest req, char *data, size_t length,size_t ) {
//                QByteArray msg;
//                if(req.getMethod() == HttpMethod::METHOD_GET){
//                    msg = (req.getUrl().toString().c_str());
//                    QByteArray result = doHandlerGet(msg);
//                    if(!result.isEmpty()){
//                        msg = result;
//                    }else{
//                        msg = "null";
//                    }
//                }else if(req.getMethod() == HttpMethod::METHOD_POST){
//                    msg = (req.getUrl().toString().c_str());
//                    QByteArray msg1(data,length);
//                    BUG << msg1;
//                    msg = GETSHA256(msg);
//                    //emit doBlockNew(msg);
//                    QtConcurrent::run(QThreadPool::globalInstance(),blockHttpd,&onnHttpd::runBlockNew,msg1);
//                }else{
//                    msg = (req.getUrl().toString().c_str());
//                    msg = GETSHA256(msg);
//                    BUG << "httpd unknow method";
//                }
//                res->end(msg.data(), msg.count());
//            });

//            // This makes use of the SO_REUSEPORT of the Linux kernel
//            // Other solutions include listening to one port per thread
//            // with or without some kind of proxy inbetween
//            if (!h.listen(blockHttpd->port, nullptr, uS::ListenOptions::REUSE_PORT)) {
//                BUG << "Failed to listen";
//            }else{
//                BUG << "httpd listen ok";
//            }
//            h.run();
//        });
//    });

//    std::for_each(threads.begin(), threads.end(), [](std::thread *t) {
//        t->join();
//    });
//}

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
        string v = con.getRequest().version;
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
        }else if(con.getRequest().method == "POST"){
            msg = (con.getRequest().body.c_str());
            con.clearData();
            resp.body = handy::Slice(GETSHA256(msg));
            //emit doBlockNew(msg);
            QtConcurrent::run(QThreadPool::globalInstance(),this,&onnHttpd::runBlockNew,msg);
        }else{
            resp.body = handy::Slice(GETSHA256(msg));
            cout << "httpd unknow method" << con.getRequest().method << endl;
        }
        con.sendResponse(resp);
        if (v == "HTTP/1.0") {
            con->close();
        }
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
