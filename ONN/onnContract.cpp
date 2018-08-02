#include "onnContract.h"

onnContract::onnContract()
{

}

void onnContract::onStart(){
    std::cout << "contract start" << std::endl;
    qint64 i = 0;
    for(auto curContract:getContracts()){
        for(i=getBlock(curContract).blockIndex.toLongLong();;i++){
            QByteArray curKey = "0-";
            QByteArray prvValue = getDatabaseBlock(curKey+QByteArray::number(i-1));
            QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
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
    }
    emit doStartFinish();
}
