#include "onnHttpd.h"
#include <handy/handy.h>

onnHttpd::onnHttpd()
{

}

void onnHttpd::runBlockNew(QByteArray pData){
    onBlockNew(pData);
}

void onnHttpd::onStart(){
    std::cout << "httpd start" << std::endl;
    int threads = 100;
    handy::setloglevel("FATAL");
    handy::MultiBase base(threads);
    handy::HttpServer sample(&base);
    int curPort = 3000;
    if(!getArgument("-p").isEmpty()){
        curPort = getArgument("-p").toInt();
    }
    int r = sample.bind("", curPort);
    if(r){cout<<"runHttp failed:"<<curPort<<endl;exit(-1);}
    sample.onDefault([&](const handy::HttpConnPtr& con){
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
    flagStart = true;
    emit doStartFinish();
    handy::Signal::signal(SIGINT, [&]{base.exit();});
    base.loop();
}
