#include "onnDatabase.h"

onnDatabase::onnDatabase()
{

}

void onnDatabase::onStart(){
    std::cout << "database start" << std::endl;
    qint64 i = 0;
    if(getDatabaseBlock("0-0") == "null"){
        setDatabaseBlock("0-0",getBlock0());
        emit doBlockOld(getDatabaseBlock("0-0"));
        emit doStartFinish();
        return;
    }
    setDatabaseBlock("0-0",getBlock0());
    emit doBlockOld(getDatabaseBlock("0-0"));
    /*
    for(i=1;;i++){
        QByteArray curKey = "0-";
        QByteArray prvValue = getDatabaseBlock(curKey+QByteArray::number(i-1));
        QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
        if(i==1){
            prvValue = getBlock0();
        }
        if(curValue == "null"){
            break;
        }
        onnBlock curBlock = createBlock(curValue);
        onnBlock prvBlock = createBlock(prvValue);
        if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
            BUG << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
            break;
        }
        if(curBlock.blockHashPrev!=prvBlock.blockHash){
            BUG << "curBlock.blockHashPrev!=prvBlock.blockHash";
            break;
        }
        emit doBlockOld(curValue);
    }
    emit doStartFinish();
    */
}
