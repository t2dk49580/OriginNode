#include "onnDatabase.h"

onnDatabase::onnDatabase(){

}

void onnDatabase::onStart(){
    std::cout << "database start" << std::endl;
    if(getDatabaseBlock("0-0") == "null"){
        setDatabaseBlock("0-0",getBlock0());
        emit doBlockOld(getDatabaseBlock("0-0"));
        emit doStartFinish();
        return;
    }
    setDatabaseBlock("0-0",getBlock0());
    emit doBlockOld(getDatabaseBlock("0-0"));
}
