#include "onnObject.h"
#include <QMultiMap>

QSettings *onnSetting;
onnKey onnObjectKey;
QHash<QString,QString> onnArgument;
QHash<QByteArray,QByteArray> onnBoss;
QMultiHash<QByteArray,QByteArray> onnBossforAddress;
leveldb::DB *onnObjectDB;
QStringList onnReadableContract;
QHash<QString,onnBossBlock> *onnBlockChain = new QHash<QString,onnBossBlock>;
QHash<QString,lua_State *> *onnObjectContract = new QHash<QString,lua_State *>;
Hub *onnWebsocket = new Hub();
NetSync *onnSync;
QStringList onnPeerList;
QStringList onnPeerLose;
QTimer *onnTimer = new QTimer();
QList<QByteArray> onnWebsocketAddress;
QList<QByteArray> onnWebsocketPeers;
QHash<QString,onnSyncQueue> onnSyncData;
QHash<QString,onnSyncQueue> onnSyncRequest;
QHash<QString,onnSyncQueue> onnSyncResponse;
int onnSyncRequestCount = 0;
int onnSyncResponseCount = 0;
QStringList onnClientList;
QMultiHash<QByteArray,QByteArray> onnChangeBossData;
QStringList onnBlackList;
QReadWriteLock onnRWlock;
QMutex onnLock;
int onnGas = 0;

onnObject::onnObject(QString pType){
    objType = pType;
    flagStart = false;
}
onnObject::~onnObject(){}

void onnObject::init(){emit doInit();}
void onnObject::onInit(){emit doInitFinish();}
void onnObject::onInitFinish(){}
void onnObject::onStart(){
    std::cout << "object start" << std::endl;
    flagStart = true;
    emit doStartFinish();
}
void onnObject::onStartFinish(){}

QByteArray onnObject::Encrypt(QByteArray pHex,QByteArray pMsg)
{
    BUG << pMsg;
    QByteArray result;
    QByteArray keyiv = QByteArray::fromHex(GETSHA256(QByteArray::fromHex(pHex)));
    unsigned char key[EVP_MAX_KEY_LENGTH] = {0};  //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH] = {0};   //保存初始化向量的数组
    EVP_CIPHER_CTX ctx;         //EVP加密上下文环境
    unsigned char out[1024] = {0};        //保存密文的缓冲区
    int outl;
    int rv;
    int i;

    //设置key和iv
    for(i=0;i<24;i++)
    {
        key[i]=(unsigned char)keyiv.at(i);
    }
    for(i=0;i<8;i++)
    {
        iv[i]=(unsigned char)keyiv.at(i+24);
    }

    //初始化ctx
    EVP_CIPHER_CTX_init(&ctx);
    rv = EVP_EncryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
    if(rv != 1)
    {
        printf("Err\n");
        return result;
    }
    rv = EVP_EncryptUpdate(&ctx,out,&outl,(const unsigned char *)pMsg.data(),pMsg.count());//加密
    if(rv != 1)
    {
        //fail
        return result;
    }
    result.append((const char *)out,outl);
    rv = EVP_EncryptFinal_ex(&ctx,out,&outl);
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return result;
    }
    QByteArray result1;
    result1.append((const char *)out,outl);
    BUG << result.toHex();
    BUG << result1.toHex();
    EVP_CIPHER_CTX_cleanup(&ctx);   //清除EVP加密上下文环境
    return (result+result1).toHex();
}

QByteArray onnObject::Decrypt(QByteArray pHex,QByteArray pMsg)
{
    BUG << pMsg;
    QByteArray result;
    QByteArray secmsg = QByteArray::fromHex(pMsg);
    QByteArray keyiv = QByteArray::fromHex(GETSHA256(QByteArray::fromHex(pHex)));
    unsigned char key[EVP_MAX_KEY_LENGTH] = {0};      //保存密钥的数组
    unsigned char iv[EVP_MAX_KEY_LENGTH] = {0};       //保存初始化向量的数组
    EVP_CIPHER_CTX ctx;             //EVP加密上下文环境
    unsigned char out[1024+EVP_MAX_KEY_LENGTH] = {0}; //保存解密后明文的缓冲区数组
    int outl;
    int rv;
    int i;

    for(i=0;i<24;i++)
    {
        key[i]=(unsigned char)keyiv.at(i);
    }
    for(i=0;i<8;i++)
    {
        iv[i]=(unsigned char)keyiv.at(i+24);
    }

    //初始化ctx
    EVP_CIPHER_CTX_init(&ctx);
    rv = EVP_DecryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return result;
    }
    rv = EVP_DecryptUpdate(&ctx,out,&outl,(const unsigned char *)secmsg.data(),secmsg.count());//解密
    if(rv != 1)
    {
        //fail
        EVP_CIPHER_CTX_cleanup(&ctx);
        return result;
    }
    result.append((const char *)out,outl);

    rv = EVP_DecryptFinal_ex(&ctx,out,&outl);
    if(rv != 1)
    {
        EVP_CIPHER_CTX_cleanup(&ctx);
        return result;
    }
    QByteArray result1;
    result1.append((const char *)out,outl);
    EVP_CIPHER_CTX_cleanup(&ctx);//清除EVP加密上下文环境
    BUG << result+result1 << (result+result1).count();
    return result+result1;
}

QByteArray onnObject::getBlock0(){
    QFile f("0");
    f.open(QIODevice::ReadOnly);
    QByteArray curBlock0 = f.readAll();
    f.close();
    return curBlock0;
}

void onnObject::makeBlock0(){
    QFile f("0.lua");
    f.open(QIODevice::ReadOnly);
    QByteArray curContract = f.readAll();
    f.close();
    QByteArray curData = doDeploy("0",curContract.toHex(),QByteArray("null").toHex());
    onnBlock curBlock = createBlock(0,0,getHash(curData).toHex(),curData);
    QFile f1("0");
    f1.open(QIODevice::WriteOnly);
    f1.write(toString(curBlock));
    f1.close();
}

void onnObject::initKey(){
    string curAppkey;
    QString curFile = "key.ini";
    if(!getArgument("-f").isEmpty()){
        curFile = getArgument("-f");
    }
    onnSetting = new QSettings(curFile,QSettings::IniFormat);
    if(hasAppkey()){
        onnObjectKey.appkey = onnSetting->value("appkey").toString().toLatin1();
        cout << "Enter your password" << endl;
        cin>>curAppkey;
        if(onnObjectKey.appkey != GETPSD(curAppkey.c_str())){
            cout << "password not correct" << endl;
            exit(-1);
        }
    }else{
        while(curAppkey.size()<6){
            curAppkey.clear();
            cout << "Enter a new password (length must be >= 6)" << endl;
            cin>>curAppkey;
        }
        onnObjectKey.appkey = GETPSD(curAppkey.c_str());
        onnSetting->setValue("appkey",onnObjectKey.appkey);
    }
    if(hasPubkey()){
        onnObjectKey.pubkey = onnSetting->value("pubkey").toString().toLatin1();
        onnObjectKey.prikey = Decrypt(GETSHA256(curAppkey.c_str()),onnSetting->value("prikey").toString().toLatin1());
    }else{
        makeKey(GETSHA256(curAppkey.c_str()));
    }
    onnObjectKey.address = GETADDR(onnObjectKey.pubkey);
}

QByteArray onnObject::computePubkey(QByteArray pPri){
    uint8_t pp[65] = {0};
    uECC_compute_public_key((uint8_t *)QByteArray::fromHex(pPri).data(),pp,uECC_secp256k1());
    QByteArray final = (char *)pp;
    return final.toHex();
}

bool onnObject::hasAppkey(){
    if (!onnSetting->contains("appkey")){
        return false;
    }
    return true;
}

void onnObject::updAppkey(QByteArray pKey){
    onnObjectKey.appkey = pKey;
    onnSetting->setValue("appkey",onnObjectKey.appkey);
}

bool onnObject::hasPubkey(){
    if (!onnSetting->contains("pubkey")){
        return false;
    }
    return true;
}

void onnObject::makeKey(QByteArray pHex){
    getkey();
    onnObjectKey.pubkey = getPublicKey();
    onnObjectKey.prikey = getPrivateKey();
    onnObjectKey.prikey = onnObjectKey.prikey.left(64);   //need use AES

    onnSetting->setValue("pubkey",onnObjectKey.pubkey);
    onnSetting->setValue("prikey",Encrypt(pHex,onnObjectKey.prikey));
}

QByteArray onnObject::getSignature(QByteArray pMsg){
    QByteArray hash = GETSHA256(pMsg);
    sign(onnObjectKey.prikey.data(),hash.data());
    return QByteArray(getSign()).left(128);
}

QByteArray onnObject::getSignHash(QByteArray pHash){
    sign(onnObjectKey.prikey.data(),pHash.data());
    return QByteArray(getSign()).left(128);
}

QByteArray onnObject::getPubkey(){
    return onnObjectKey.pubkey;
}
QByteArray onnObject::getPrikey(){
    return onnObjectKey.prikey;
}
QByteArray onnObject::getAddress(){
    return onnObjectKey.address;
}

QByteArray onnObject::getHash(QByteArray pData){
    return QCryptographicHash::hash(pData,QCryptographicHash::Sha256);
}

bool onnObject::getVerify(QByteArray pub1,QByteArray msg1,QByteArray sig1){
    if(pub1.count()!=128 || sig1.count()!=128)return false;
    FieldElem x,y;
    Number msg,r,s;
    GroupElemJac pub;
    Signature sig;
    x.SetHex(pub1.left(64).data());
    y.SetHex(pub1.right(64).data());
    GroupElem aff(x,y);
    pub.SetAffine(aff);
    msg.SetHex(getHash(msg1).toHex().data());
    r.SetHex(sig1.left(64).data());
    s.SetHex(sig1.right(64).data());
    sig.SetRS(r,s);
    return sig.Verify(pub, msg);
}
/////////////////////////////////////////////////////////////////////////////////////////////
QString onnObject::getTaget(QString type,QString pubkey,QString name,QString code,QString arg,QString sig) {
    QString data = type + "$" + pubkey + "$" + name + "$" + code + "$" + arg;
    QString block = sig + "&" + data;
    return block;
}

QString onnObject::docmd(QString type,QString pubkey,QString prikey,QString name,QString func,QString arg) {
    QString msg = type + "$" + pubkey + "$" + name + "$" + func + "$" + arg;
    QByteArray hash = GETSHA256(msg.toLatin1());
    sign(prikey.toLatin1().data(),hash.data());
    QByteArray sig = getSign();
    sig = sig.left(128);
    QString block = getTaget(type, pubkey, name, func, arg, sig);
    return block;
}

QByteArray onnObject::doMethodGet(QString pContract,QString pMethod,QString pArg){
    QString block = pContract+"$"+pMethod+"$"+pArg+"$"+getPubkey();
    return block.toLatin1();
}
QByteArray onnObject::doMethodSet(QString pContract, QString pMethod, QString pArg){
    QString block = docmd("method",getPubkey(),getPrikey(),pContract,pMethod,pArg);
    return block.toLatin1();
}
QByteArray onnObject::doCustomSet(QString pType,QString pContract,QString pMethod,QString pArg){
    QString block = docmd(pType,getPubkey(),getPrikey(),pContract,pMethod,pArg);
    return block.toLatin1();
}
QByteArray onnObject::doDeploy(QString pContract,QString pCode,QString pArg){
    QString block = docmd("deploy",getPubkey(),getPrikey(),pContract,pCode,pArg);
    return block.toLatin1();
}
QByteArray onnObject::doHandlerGet(QByteArray pData){
    if(pData.contains("$")){
        pData.remove(0,1);
        return doMethodGet(pData);
    }
    if(pData.left(5) == "/help" || pData == "/favicon.ico"){
        QStringList helpInfo;
        helpInfo.append("/help");
        helpInfo.append("/list");
        helpInfo.append("/last + 0");
        helpInfo.append("/block + 0-0");
        helpInfo.append("/peers");
        helpInfo.append("/maker + contract");
        helpInfo.append("/boss + pub");
        helpInfo.append("/balance + contract,pub");
        helpInfo.append("/address");
        return helpInfo.join("\n").toLatin1();
    }
    if(pData == "/list"){
        return getContracts().join("\n").toLatin1();
    }
    if(pData.left(5) == "/last"){
        return toString(getBlock(pData.remove(0,5)));
    }
    if(pData.left(6) == "/block"){
        return getDatabaseBlock(pData.remove(0,6));
    }
    if(pData.left(6) == "/peers"){
        BUG << getPeerList();
        return getPeerList().join("\n").toLatin1();
    }
    if(pData.left(6) == "/maker"){
        return getBoss(pData.remove(0,6));
    }
    if(pData.left(5) == "/boss"){
        return getBossFromAddress(pData.remove(0,5)).join("\n");
    }
    if(pData.left(8) == "/balance"){
        return QByteArray::number(getContractBalance(pData.remove(0,8).split(',').first(),pData.remove(0,8).split(',').last()));
    }
    if(pData.left(8) == "/address"){
        return onnObjectKey.address;
    }
    pData.remove(0,1);
    return doMethodGet(pData);
}
////////////////////////////////////////////////////////////////////////////////////////
void onnObject::initArgv(int argc, char *argv[]){
    QString onnVersion = "0.9.1.4";
    if(argc>1){
        for(int i=1;i<argc;i=i+2){
            if(i+1>argc)
                break;
            onnArgument.insert(argv[i],argv[i+1]);
        }
    }
    if(onnArgument.contains("-h")){
        cout << "usage：ONN [option]" << endl;
        cout << "    -p     RPC listen port, default 3000" << endl;
        cout << "    -ws    websocket listen port, default 3001" << endl;
        cout << "    -i     import a key file, default key.ini" << endl;
        cout << "    -t     set contract name, enable timer for run contract function _timeout()" << endl;
        cout << "    -s     set msec timer step when you use -t" << endl;
        cout << "    -v     show version" << endl;
        cout << "    -h     show this info" << endl;
        exit(1);
    }
    if(onnArgument.contains("-v")){
        cout << onnVersion.toStdString() << endl;
        exit(1);
    }
}

QString onnObject::getArgument(QString pKey){
    if(onnArgument.contains(pKey)){
        return onnArgument.value(pKey);
    }
    return "";
}
QString onnObject::getLocalIP(){
    QString ipAddr;
    QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
    for(QHostAddress address:AddressList){
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            if (address.toString().contains("127.0.")){
                continue;
            }
            return address.toString();
        }
    }
    return ipAddr;
}
void onnObject::setPeerList(QStringList pList){
    onnPeerList = pList;
}
void onnObject::setPeerLose(QStringList pList){
    onnPeerLose = pList;
}
QStringList onnObject::getPeerList(){
    return onnPeerList;
}
QStringList onnObject::getPeerLose(){
    return onnPeerLose;
}
QByteArray onnObject::calcHash(onnBlock pBlock){
    return getHash(pBlock.blockIndex+\
                              pBlock.blockTimestamp+\
                              pBlock.blockHashPrev+\
                              pBlock.blockData+\
                              pBlock.blockMaker).toHex();
}
void onnObject::setUdpClientList(QStringList pList){
    onnClientList = pList;
}
QStringList onnObject::getUdpClientList(){
    return onnClientList;
}
bool onnObject::hasUdpClientList(QString pAddress){
    return onnClientList.contains(pAddress);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::initDatabase(){
    QString pFile = "db";
    if(!getArgument("-d").isEmpty()){
        pFile = getArgument("-d");
    }
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, pFile.toLatin1().data(), &onnObjectDB);
    assert(status.ok());
}

QByteArray onnObject::getDatabaseBlock(QByteArray pKey){
    string value;
    leveldb::Status s;
    s = onnObjectDB->Get(leveldb::ReadOptions(), pKey.data(), &value);
    if(!s.ok()){
        return "null";
    }
    return value.c_str();
}
bool onnObject::setDatabaseBlock(QByteArray pKey,QByteArray pVar){
    leveldb::WriteOptions write_options;
    write_options.sync = true;
    leveldb::Status s = onnObjectDB->Put(leveldb::WriteOptions(), pKey.data(), pVar.data());
    if (!s.ok()){
        cout << "setData fail:" << pKey.data() << pVar.data() << endl;
    }
    return s.ok();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::insertBlock(QString pContract,onnBlock pBlock){
    onnBossBlock curBlock;
    if(onnBlockChain->contains(pContract)){
        curBlock = onnBlockChain->value(pContract);
    }else{
        curBlock.blockDeploy  = pBlock;
    }
    curBlock.name = pContract.toLatin1();
    curBlock.blockCurrent = pBlock;
    onnBlockChain->insert(pContract,curBlock);
}
onnBlock onnObject::getBlock(QString pContract){
    onnBlock curBlock;
    if(hasBlock(pContract.toLatin1()))
        return onnBlockChain->value(pContract).blockCurrent;
    return curBlock;
}
onnBossBlock onnObject::getBossBlock(QString pContract){
    onnBossBlock curBlock;
    if(hasBlock(pContract.toLatin1()))
        return onnBlockChain->value(pContract);
    return curBlock;
}
QByteArray onnObject::toString(onnBlock pBlock){
    return pBlock.blockIndex+"@"+pBlock.blockTimestamp+"@"+pBlock.blockHashPrev+"@"+pBlock.blockHash\
            +"@"+pBlock.blockData+"@"+pBlock.blockMaker+"@"+pBlock.blockMakerSign;
}

bool onnObject::hasBlock(QByteArray pKey){
    return onnBlockChain->contains(pKey);
}
onnBlock onnObject::createBlock(QByteArray pData){
    onnBlock curBlock;
    QList<QByteArray> data = pData.split('@');
    if(data.count()<7)
        return curBlock;
    curBlock.blockIndex = data.at(0);
    curBlock.blockTimestamp = data.at(1);
    curBlock.blockHashPrev = data.at(2);
    curBlock.blockHash = data.at(3);
    curBlock.blockData = data.at(4);
    curBlock.blockMaker = data.at(5);
    curBlock.blockMakerSign = data.at(6);
    return curBlock;
}
onnBlock onnObject::createBlock(qint64 pIndex,qint64 pTime,QString pHashPrev,QByteArray pData){
    onnBlock curBlock;
    curBlock.blockIndex = QByteArray::number(pIndex);
    curBlock.blockTimestamp = QByteArray::number(pTime);//QDateTime::currentMSecsSinceEpoch()
    curBlock.blockHashPrev = pHashPrev.toLatin1();
    curBlock.blockData = pData;
    curBlock.blockMaker = getPubkey();
    curBlock.blockHash = calcHash(curBlock);
    curBlock.blockMakerSign = getSignHash(curBlock.blockHash);
    return curBlock;
}
//////////////////////////////////////////////////////////////////////////////////////////
QString onnObject::doGetRandom(){
    QString result;
    _doMethodR(getContract("0"),"_doRand",QString::number(getPeerList().count()),getPubkey(),result);
    return result;
}
QString onnObject::doGetRandom(int pMax){
    QString result;
    _doMethodR(getContract("0"),"_doRand",QString::number(pMax),getPubkey(),result);
    return result;
}
bool onnObject::_doMethod(QString pContract,QString pFunction,QString pArg,QString pkey,QString &pResult){
    onnLock.lock();
    lua_State *luaInterface = getContract(pContract.toLatin1());
    if(!luaInterface){
        onnLock.unlock();
        pResult = "method fail: contract not exist";
        return false;
    }
    bool curResult = _doMethod(luaInterface,pFunction,pArg,pkey,pResult);
    onnLock.unlock();
    return curResult;
}
bool onnObject::_doMethod(lua_State *luaInterface,QString pFunction,QString pArg,QString pkey,QString &ret){
    lua_getglobal(luaInterface, "_setUser");
    lua_pushstring(luaInterface, pkey.toLatin1().data());
    if(lua_pcall(luaInterface, 1, 1, 0) != 0){
        BUG << "error _setUser" << lua_tostring(luaInterface,-1);
        ret = QString("error lua_pcall _setUser ")+QString(__LINE__)+","+pFunction+","+pArg+","+pkey;
        onnGas = lua_getGas();
        lua_resetGas();
        return false;
    }
    lua_settop(luaInterface,0);

    int arglen = 0;
    lua_getglobal(luaInterface, pFunction.toLatin1().data());
    if(pArg == "null"){
        arglen = 0;
    }else if(!pArg.contains("?")){
        arglen = 1;
        lua_pushstring(luaInterface, pArg.toLatin1().data());
    }else{
        auto curArg = pArg.split("?");
        arglen = curArg.count();
        for(int i=0;i<arglen;i++){
            lua_pushstring(luaInterface, curArg.at(i).toLatin1().data());
        }
    }
    //PrintLuaStack(luaInterface);
    if(lua_pcall(luaInterface, arglen, 1, 0) != 0){
        BUG << "error lua_pcall" << pFunction << pArg << lua_tostring(luaInterface,-1);;
        ret = QString("error lua_pcall _setUser ")+QString(__LINE__)+","+pFunction+","+pArg+","+pkey;
        onnGas = lua_getGas();
        lua_resetGas();
        return false;
    }
    if(lua_isstring(luaInterface, 1)){
        ret = lua_tostring(luaInterface, 1);
    }else if(lua_isinteger(luaInterface, 1) || lua_isnumber(luaInterface, 1)){
        ret = QString::number(lua_tointeger(luaInterface, 1));
    }else if(lua_isnumber(luaInterface, 1)){
        ret = QString::number(lua_tonumber(luaInterface, 1));
    }else{
        ret = "null";
    }
    onnGas = lua_getGas();
    lua_resetGas();
    lua_settop(luaInterface,0);
    //BUG << pFunction << onnGas;
    if(ret.left(4) == "fail")
        return false;
    return true;
}
bool onnObject::_doMethodW(lua_State *luaInterface,QString pFunction,QString pArg,QString pkey,QString &ret){
    //onnRWlock.lockForWrite();
    onnLock.lock();
    bool result = _doMethod(luaInterface,pFunction,pArg,pkey,ret);
    onnLock.unlock();
    //onnRWlock.unlock();
    return result;
}
bool onnObject::_doMethodR(lua_State *luaInterface,QString pFunction,QString pArg,QString pkey,QString &ret){
    //onnRWlock.lockForRead();
    onnLock.lock();
    bool result = _doMethod(luaInterface,pFunction,pArg,pkey,ret);
    onnLock.unlock();
    //onnRWlock.unlock();
    return result;
}
QByteArray onnObject::doMethodGet(QByteArray pMsg){
    //BUG << pMsg;
    QList<QByteArray> msgList = pMsg.split('$');
    if(msgList.count()<4){
        QString lc = "msgList.count()<4";
        return lc.toLatin1();
    }
    QString contract = msgList.at(0);
    QString method = msgList.at(1);
    QString arg = msgList.at(2);
    QString pkey = msgList.at(3);
    QString result;
    if(method.left(3) != "get"){
        QString lc = "method fail: only use get method";
        return lc.toLatin1();
    }
//    if(!hasContract(contract.toLatin1())){
//        QString lc = "method fail: contract not exist";
//        return lc.toLatin1();
//    }
    _doMethod(contract,method,QByteArray::fromHex(arg.toLatin1()),pkey,result);
    return result.toLatin1();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::addContract(QByteArray pContract,lua_State *&pInterface){
    onnReadableContract.append(pContract);
    onnObjectContract->insert(pContract,pInterface);
}

bool onnObject::hasContract(QByteArray pContract){
    return onnObjectContract->contains(pContract);
}

lua_State *onnObject::getContract(QByteArray pContract){
    return onnObjectContract->value(pContract);
}
QStringList onnObject::getContracts(){
    return onnObjectContract->keys();
}
QString onnObject::getContractOrigin(){
    QFile f("0.lua");
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    f.close();
    return data;
}
bool onnObject::checkBlockIndexAndHash(QString pName,onnBlock curBlock){
    if(!hasContract("0")){
        return true;
    }
    if(curBlock.blockIndex.toLongLong()<=getBlock(pName).blockIndex.toLongLong()){
        BUG << "msg fail: curBlock.blockIndex<=getBlock(pName).blockIndex" << pName;
        return false;
    }else if(curBlock.blockIndex.toLongLong()>getBlock(pName).blockIndex.toLongLong()+1){
        BUG << "msg fail: curBlock.blockIndex>getBlock(pName).blockIndex+1" << curBlock.blockIndex << getBlock(pName).blockIndex;
        return false;
    }

    if(curBlock.blockHashPrev != getBlock(pName).blockHash){
        BUG << "msg fail: curBlock.blockHashPrev != getBlock(pName).blockHash" << pName;
        return false;
    }

    if(getBoss(pName.toLatin1()) != GETADDR(curBlock.blockMaker)){
        BUG << "msg fail: getBoss(pName.toLatin1()) != GETADDR(curBlock.blockMaker)" << pName;
        return false;
    }
    return true;
}
bool onnObject::checkBlockIndexAndHashDeploy(QString pName,onnBlock prvBlock,onnBlock curBlock){
    if(!hasContract("0")){
        return true;
    }
    if(curBlock.blockIndex.toLongLong()<=prvBlock.blockIndex.toLongLong()){
        BUG << "msg fail: curBlock.blockIndex<=prvBlock.blockIndex" << pName;
        return false;
    }else if(curBlock.blockIndex.toLongLong()>prvBlock.blockIndex.toLongLong()+1){
        BUG << "msg fail: curBlock.blockIndex>prvBlock.blockIndex+1" << curBlock.blockIndex << getBlock(pName).blockIndex;
        return false;
    }

    if(curBlock.blockHashPrev != prvBlock.blockHash){
        BUG << "msg fail: curBlock.blockHashPrev != prvBlock.blockHash" << pName;
        return false;
    }

    if(getBoss("0") != GETADDR(curBlock.blockMaker)){
        BUG << "msg fail: curIdentityPubkey 0 != GETADDR(curBlock.blockMaker)" << pName;
        return false;
    }
    return true;
}
bool onnObject::checkBlockNewIdentity(QString pName, QByteArray pData){
    QByteArray curBoss = getBoss(pName.toLatin1());
    if(curBoss.isEmpty()){
        return false;
    }
    if(curBoss != onnObjectKey.address){
        BUG << "send to boss" << pName << getBoss(pName.toLatin1());
        //emit doSendBlockChainData(pName,curIdentityPubkey,pData);
        emit doCustomRequire(pName,getBoss(pName.toLatin1()),"newblock",pData);
        return false;
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::setBoss(QByteArray pContract,QByteArray pAddress){
    BUG << pContract << pAddress;
    if(onnBoss.contains(pContract)){
        rmBossFromAddress(onnBoss.value(pContract));
    }
    onnBoss.insert(pContract,pAddress);
    onnBossforAddress.insert(pAddress,pContract);
}
QByteArray onnObject::getBoss(QByteArray pContract){
    return onnBoss.value(pContract);
}
void onnObject::rmBoss(QByteArray pContract){
    onnBoss.remove(pContract);
}
void onnObject::rmBossFromAddress(QByteArray pAddress){
    onnBossforAddress.remove(pAddress);
}
QByteArrayList onnObject::getBossFromAddress(QByteArray pAddress){
    return onnBossforAddress.values(pAddress);
}
QByteArrayList onnObject::getBossAddressList(){
    return onnBoss.values();
}
QStringList onnObject::getBossLose(QStringList pLose){
    QStringList result;
    QByteArrayList curBossList = onnBoss.values();
    for(auto curAddress:pLose){
        if(curBossList.contains(curAddress.toLatin1())){
            if(!result.contains(curAddress)){
                result.append(curAddress);
            }
        }
    }
    return result;
}
QByteArrayList onnObject::getBossMissing(QStringList pList){
    QByteArrayList curBossList = onnBoss.values();
    for(auto curAddress:pList){
        if(curBossList.contains(curAddress.toLatin1())){
            curBossList.removeAll(curAddress.toLatin1());
        }
    }
    return curBossList;
}
QByteArrayList onnObject::getBossMissingContracts(){
    QByteArrayList result;
    QStringList curContracts = getContracts();
    for(auto curContract:curContracts){
        QByteArray curMaker = getBoss(curContract.toLatin1());
        if(!getPeerList().contains(curMaker)){
            result.append(curContract.toLatin1());
        }
    }
    return result;
}
QStringList onnObject::getOnlyWork(QStringList pList){
    QStringList result;
    QByteArrayList curBossList = getBossAddressList();
    for(auto curAddress:pList){
        if(!curBossList.contains(curAddress.toLatin1())){
            result.append(curAddress);
        }
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::initNetSync(){
    onnSync = new NetSync();
    onnSync->Init(GETADDR(getPubkey()));
}
NetSync *onnObject::getNetSync(){
    return onnSync;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::initWebsocketd(){
    onnWebsocket->onConnection([&](uWS::WebSocket<uWS::SERVER> *ws, HttpRequest) {
        cout << ws->getAddress().address << endl;
        if(onnWebsocketAddress.contains(ws->getAddress().address)){
            ws->close();
        }else{
            onnWebsocketAddress.append(ws->getAddress().address);
            onnWebsocketPeers.append(QByteArray(ws->getAddress().address).remove(0,7)+":"+QByteArray::number(ws->getAddress().port));
        }
    });
    onnWebsocket->onDisconnection([&](uWS::WebSocket<uWS::SERVER> *ws, int, char *, size_t) {
        onnWebsocketAddress.removeAll(ws->getAddress().address);
        onnWebsocketPeers.removeAll(QByteArray(ws->getAddress().address)+":"+QByteArray::number(ws->getAddress().port));
    });
}
Hub *onnObject::getWebsocketd(){
    return onnWebsocket;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::setSyncQueue(QByteArray pContract,QByteArray pAddress,QByteArray pKey,QByteArray pStart,QByteArray pEnd){
    onnSyncQueue queue;
    queue.blockContract = pContract;
    queue.blockAddress = pAddress;
    queue.blockStart = pStart;
    queue.blockEnd = pEnd;
    queue.blockLastModify = QDateTime::currentMSecsSinceEpoch();
    if(pKey=="request"){
        onnSyncRequestCount++;
        onnSyncRequest.insert(pContract+"-"+pAddress+"-"+pKey,queue);
    }else if(pKey=="response"){
        onnSyncResponseCount++;
        onnSyncResponse.insert(pContract+"-"+pAddress+"-"+pKey,queue);
    }
    //onnSyncData.insert(pContract+"-"+pAddress+"-"+pKey,queue);
}
bool onnObject::updSyncQueueIndex(QByteArray pContract,QByteArray pAddress,QByteArray pKey,QByteArray pIndex){
    onnSyncQueue curData;// = onnSyncData.value(pContract+"-"+pAddress+"-"+pKey);
    if(pKey=="request"){
        curData = onnSyncRequest.value(pContract+"-"+pAddress+"-"+pKey);
    }else if(pKey=="response"){
        curData = onnSyncResponse.value(pContract+"-"+pAddress+"-"+pKey);
    }
    if(curData.blockCurrentIndex.toLongLong()<pIndex.toLongLong()){
        curData.blockCurrentIndex = pIndex;
        curData.blockLastModify = QDateTime::currentMSecsSinceEpoch();
    }else{
        return true;
    }
    if(pKey=="request"){
        onnSyncRequest.insert(pContract+"-"+pAddress+"-"+pKey,curData);
    }else if(pKey=="response"){
        onnSyncResponse.insert(pContract+"-"+pAddress+"-"+pKey,curData);
    }
    //onnSyncData.insert(pContract+"-"+pAddress+"-"+pKey,curData);
    if(pIndex.toLongLong()>=curData.blockEnd.toLongLong()){
        return false;
    }else{
        return true;
    }
}
onnSyncQueue onnObject::getSyncQueue(QByteArray pContract,QByteArray pAddress,QByteArray pKey){
    if(hasSyncQueue(pContract,pAddress,pKey)){
        if(pKey=="request"){
            return onnSyncRequest.value(pContract+"-"+pAddress+"-"+pKey);
        }else if(pKey=="response"){
            return onnSyncResponse.value(pContract+"-"+pAddress+"-"+pKey);
        }
        //return onnSyncData.value(pContract+"-"+pAddress+"-"+pKey);
    }
    return onnSyncQueue();
}
onnSyncQueue onnObject::getSyncQueue(QStringList pList){
    QByteArray pContract = pList.at(0).toLatin1();
    QByteArray pAddress = pList.at(1).toLatin1();
    QByteArray pKey = pList.at(2).toLatin1();
    if(hasSyncQueue(pContract,pAddress,pKey)){
        if(pKey=="request"){
            return onnSyncRequest.value(pContract+"-"+pAddress+"-"+pKey);
        }else if(pKey=="response"){
            return onnSyncResponse.value(pContract+"-"+pAddress+"-"+pKey);
        }
        //return onnSyncData.value(pContract+"-"+pAddress+"-"+pKey);
    }
    return onnSyncQueue();
}
QList<onnSyncQueue> onnObject::getSyncQueueList(QByteArray pContract,QByteArray pType){
    QList<onnSyncQueue> result;
    for(auto curData:onnSyncRequest.keys()){
        QStringList curLiist = curData.split("-");
        if(curLiist.first() == pContract && curLiist.last() == pType && curLiist.count() == 3){
            result.append(getSyncQueue(curLiist));
        }
    }
    return result;
}
bool onnObject::hasSyncQueueRequest(QByteArray pContract){
    for(auto curData:onnSyncRequest.keys()){
        if(curData.split("-").first() == pContract){
            return true;
        }
    }
    return false;
}
bool onnObject::hasSyncQueue(QByteArray pContract,QByteArray pAddress,QByteArray pKey){
    if(pKey=="request"){
        if(onnSyncRequest.contains(pContract+"-"+pAddress+"-"+pKey)){
            return true;
        }
    }else if(pKey=="response"){
        if(onnSyncResponse.contains(pContract+"-"+pAddress+"-"+pKey)){
            return true;
        }
    }
//    if(onnSyncData.contains(pContract+"-"+pAddress+"-"+pKey)){
//        return true;
//    }
    return false;
}
void onnObject::rmSyncQueue(QByteArray pContract,QByteArray pAddress,QByteArray pKey){
    //onnSyncData.remove(pContract+"-"+pAddress+"-"+pKey);
    if(pKey=="request"){
        onnSyncRequestCount--;
        onnSyncRequest.remove(pContract+"-"+pAddress+"-"+pKey);
    }else if(pKey=="response"){
        onnSyncResponseCount--;
        onnSyncResponse.remove(pContract+"-"+pAddress+"-"+pKey);
    }
}
void onnObject::rmSyncLose(QStringList pLose){
    for(auto curAddress:pLose){
        for(auto curContract:getContracts()){
            if(hasSyncQueue(curContract.toLatin1(),curAddress.toLatin1(),QString("request").toLatin1())){
                rmSyncQueue(curContract.toLatin1(),curAddress.toLatin1(),QString("request").toLatin1());
            }
            if(hasSyncQueue(curContract.toLatin1(),curAddress.toLatin1(),QString("response").toLatin1())){
                rmSyncQueue(curContract.toLatin1(),curAddress.toLatin1(),QString("response").toLatin1());
            }
        }
    }
}
int onnObject::getSyncRequestCount(){
    return onnSyncRequestCount;
}
int onnObject::getSyncResponseCount(){
    return onnSyncResponseCount;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::appendChangeBossRequest(QByteArray pBoss, QByteArray pData){
    onnChangeBossData.insertMulti(pBoss,pData);
}
bool onnObject::hasChangeBossRequest(QByteArray pBoss){
    return onnChangeBossData.contains(pBoss);
}
bool onnObject::hasChangeBossWorkerRequest(QByteArray pRequest){
    if(!onnChangeBossData.isEmpty())
        return onnChangeBossData.values().contains(pRequest);
    return false;
}
QByteArrayList onnObject::getChangeBossRequest(QByteArray pBoss){
    if(onnChangeBossData.contains(pBoss)){
        return onnChangeBossData.values(pBoss);
    }
    return QByteArrayList();
}
void onnObject::rmChangeBossRequest(QByteArray pBoss){
    onnChangeBossData.remove(pBoss);
}
double onnObject::getContractBalance(QByteArray pContract,QByteArray pAddress){
    if(!hasContract(pContract)){
        return 0;
    }
    QString result;
    if(_doMethodR(getContract(pContract),"_getBalanceOf",pAddress,pAddress,result)){
        if(result=="fail")
            return 0;
        return result.toDouble();
    }
    return 0;
}
double onnObject::getOnnBalance(QByteArray pAddr){
    QString result;
    if(_doMethodR(getContract("0"),"_getBalanceOf",pAddr,pAddr,result)){
        return result.toDouble();
    }
    return 0;
}
QByteArray onnObject::getOnnBossOwner(QByteArray pBoss){
    QString result;
    if(!hasContract(pBoss)){
        return "";
    }
    if(_doMethodR(getContract(pBoss),"_getOwner","null",onnObjectKey.address,result)){
        return result.toLatin1();
    }
    return "";
}
QByteArray onnObject::getOnnBossTotal(QByteArray pSymbol){
    QString result;
    if(!hasContract(pSymbol)){
        return "fail";
    }
    if(_doMethodR(getContract(pSymbol),"_getTotal","null",onnObjectKey.address,result)){
        return result.toLatin1();
    }
    return "fail";
}
QByteArray onnObject::getOnnBossMaker(QByteArray pSymbol){
    QString result;
    if(!hasContract(pSymbol)){
        return "fail";
    }
    if(_doMethodR(getContract(pSymbol),"getBossMaker",pSymbol,onnObjectKey.address,result)){
        return result.toLatin1();
    }
    return "fail";
}
QByteArray onnObject::setOnnBossMaker(QByteArray pSymbol, QByteArray pAddress){
    QString result;
    if(!hasContract(pSymbol)){
        return "fail";
    }
    if(_doMethodW(getContract(pSymbol),"setBossMaker",pSymbol+"?"+pAddress,onnObjectKey.address,result)){
        setBoss(pSymbol,pAddress);
        return result.toLatin1();
    }
    return "fail";
}
QString onnObject::setNextBoss(QString pArg){
    QString curResult;
    _doMethodW(getContract("0"),"_setNextBoss",pArg,onnObjectKey.address,curResult);
    if(curResult.isEmpty() || curResult.left(4) == "fail"){
        BUG << curResult;
        curResult = "fail";
    }
    return curResult;
}
QString onnObject::setDeployBoss(QString pArg, QString pKey){
    QString curResult;
    if(!_doMethodW(getContract("0"),"_setDeployBoss",pArg,pKey,curResult)){
        BUG << "fail";
        return "fail";
    }
    if(curResult.isEmpty() || curResult.left(4) == "fail"){
        BUG << curResult;
        curResult = "fail";
    }
    return curResult;
}
QString onnObject::setPeers(){
    QString curResult;
    _doMethodW(getContract("0"),"_setPeers",getPeerList().join(","),onnObjectKey.address,curResult);
    return curResult;
}
QByteArray onnObject::doOnnTransfer(QByteArray pSender,QByteArray pRecver,QByteArray pNumber){
    QString result;
    if(!hasContract("0")){
        return "fail";
    }
    if(_doMethodW(getContract("0"),"transfer",pRecver+"?"+pNumber,pSender,result)){
        return result.toLatin1();
    }
    return "fail";
}
bool onnObject::doOnnDestroy(QString pSymbol,QString pKey){
    QString result;
    if(!hasContract(pSymbol.toLatin1())){
        return false;
    }
    return _doMethodW(getContract(pSymbol.toLatin1()),"_destroy",pSymbol,pKey,result);
}
QMultiMap<qint64,QString> onnObject::getOnnBalanceUserList(QStringList pList){
    QMultiMap<qint64,QString> result;
    for(auto curAddr:pList){
        double curBalance = getOnnBalance(curAddr.toLatin1());
        result.insertMulti(curBalance,curAddr);
    }
    return result;
}
QStringList onnObject::getHaveBalanceWorker0(QStringList pList,qint64 pNumber){
    QStringList result;
    for(auto curPeer:pList){
        if(getOnnBalance(curPeer.toLatin1())<(double)pNumber){
            continue;
        }
        result.append(curPeer);
    }
    return result;
}
bool onnObject::checkCustomNetData(QByteArray pData, QByteArray pType, onnData &pResult){
    QList<QByteArray> listCmd = pData.split('&');
    if(listCmd.count()<2){
        BUG << "bad data: listCmd.count()<2" << pData;
        return false;
    }
    QByteArray sign = listCmd.at(0);
    QByteArray data = listCmd.at(1);
    QList<QByteArray> listData = data.split('$');
    if(listData.count()<5){
        BUG << "bad data: listData.count()<5" << pData;
        return false;
    }

    QByteArray type = listData.at(0);
    QByteArray pubkey = listData.at(1);
    QByteArray name = listData.at(2);
    QByteArray code = listData.at(3);
    QByteArray arg  = listData.at(4);

    if(!getVerify(pubkey,data,sign)){
        BUG << "msg fail: verify fail";
        return false;
    }

    if(!hasBlock(name)){
        BUG << "msg fail: !hasBlock(name)";
        return false;
    }

    if(type != pType){
        BUG << "msg fail: type !=" << pType;
        return false;
    }
    pResult.blockPubkey = pubkey;
    pResult.blockContract = name;
    pResult.blockType = pType;
    pResult.blockTarget = arg;
    onnBlock curBlock;
    curBlock.blockData = pData;
    pResult.block = curBlock;

    return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void onnObject::onBlockOld(QByteArray pData){
    BUG;
    onnBlock curBlock = createBlock(pData);
    QByteArray curData = curBlock.blockData;

    QList<QByteArray> listCmd = curData.split('&');
    if(listCmd.count()<2){
        BUG << "bad data: listCmd.count()<2" << pData;
        return;
    }
    QByteArray sign = listCmd.at(0);
    QByteArray data = listCmd.at(1);
    QList<QByteArray> listData = data.split('$');
    if(listData.count()<5){
        BUG << "bad data: listData.count()<5" << pData;
        return;
    }

    QByteArray tgtData = "$";
    tgtData = tgtData+listData.at(listData.count()-2)+"$"+listData.last();
    data.remove(data.count()-tgtData.count(),tgtData.count());

    QByteArray type = listData.at(0);
    QByteArray pubkey = listData.at(1);
    QByteArray name = listData.at(2);
    QByteArray code = listData.at(3);
    QByteArray arg = QByteArray::fromHex(listData.at(4));
    QByteArray maker = curBlock.blockMaker;
    QByteArray makerSign = curBlock.blockMakerSign;
    QByteArray curBlockData =  onnObject::getHash(curBlock.blockIndex+\
                                                  curBlock.blockTimestamp+\
                                                  curBlock.blockHashPrev+\
                                                  curBlock.blockData+\
                                                  curBlock.blockMaker).toHex();
    BUG << curBlock.blockIndex << pubkey << data << sign;
    if(code == "init"){
        BUG << "bad block old: can not call init" << name;
        return;
    }
    if(getVerify(pubkey,data,sign)){
        BUG << "msg fail: verify fail" << pData;
        return;
    }

    if(getVerify(maker,curBlockData,makerSign)){
        BUG << "msg fail: maker verify fail" << pData;
        return;
    }

    if(type == "deploy"){
        if(hasBlock(name)){
            BUG << "bad deploy: contract exist" << name;
            return;
        }
        emit doDeployOld(pData);
    }else if(type == "method"){
        if(!hasBlock(name)){
            BUG << "bad method: contract not exist" << name;
            return;
        }
        if(code.left(3) == "get" || code.left(1) == "_"){
            BUG << "bad method: can not run private or get" << code ;
            return;
        }
        emit doMethodOld(pData);
    }else if(type == "peer"){
        if(!getBossFromAddress(GETADDR(maker)).contains("0")){
            BUG << "bad 0: maker != 0" << maker ;
            return;
        }
        emit doPeerOld(pData);
    }else if(type == "destroy"){
        if(!hasContract(name)){
            BUG << "bad destroy: contract not exist" << name;
            return;
        }
        if(maker != getBoss("0")){
            BUG << "bad destroy: maker != boss 0" << maker << getBoss("0");
            return;
        }
        emit doDestroyOld(pData);
    }else{
        BUG << "unknow type" << type;
    }
}
void onnObject::onDestroyOld(QByteArray pData){
    onnBlock curBlock = createBlock(pData);
    if(flagStart){
        QByteArray curHash = GETSHA256(curBlock.blockData);
        if(getDatabaseBlock(curHash) != "null"){
            BUG << "bad destroy old: hash data exist" << curHash;
            return;
        }else{
            setDatabaseBlock(curHash,curHash);
        }
    }
    QList<QByteArray> pList = curBlock.blockData.split('$');
    QString name = pList.at(2);
    QString codeHex = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    if(!hasContract(name.toLatin1())){
        BUG << "bad destroy: contract not exist" << name;
        return;
    }
    if(!doOnnDestroy(name,key)){
        BUG << "doOnnDestroy fail";
        return;
    }
    lua_State *curContract = getContract(arg.toLatin1());
    lua_close(curContract);
    onnObjectContract->remove(arg);
    rmBoss(arg.toLatin1());
    insertBlock("0",curBlock);
    emit doDestroyOldOK(pData);
}
void onnObject::onDeployOld(QByteArray pData){
    onnBlock curBlock = createBlock(pData);
    if(flagStart){
        QByteArray curHash = GETSHA256(curBlock.blockData);
        if(getDatabaseBlock(curHash) != "null"){
            BUG << "bad deploy old: hash data exist" << curHash;
            return;
        }else{
            setDatabaseBlock(curHash,curHash);
        }
    }
    QList<QByteArray> pList = curBlock.blockData.split('$');
    QString name = pList.at(2);
    QString codeHex = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    if(hasContract(name.toLatin1())){
        BUG << "bad deploy: contract exist" << pData;
        return;
    }
    if(!checkBlockIndexAndHashDeploy(name,getBlock("0"),curBlock)){
        return;
    }
    QString code;
    if(codeHex.contains("i")){
        code = codeHex;
    }else{
        code = QByteArray::fromHex(codeHex.toLatin1());
    }
    if(code.contains("_G") && name != "0"){
        BUG << "bad deploy: contains _G" << name;
        return;
    }
    QString codeCost = QString::number(code.count()*2);
    //code.push_front(contractHead);
    lua_State *luaInterface = luaL_newstate();
    luaL_openlibs1(luaInterface);
    luaL_dostring(luaInterface,code.toLatin1().data());
    QString result;
    QString resultInit;
    if(!_doMethodW(luaInterface,"init",arg,key,resultInit)){
        lua_close(luaInterface);
        return;
    }
    QString curTotal;
    if(_doMethodR(luaInterface,"_getTotal","null",onnObjectKey.address,result)){
        curTotal = result;
    }else{
        curTotal = "0";
        BUG << "_getTotal fail" << result;
        lua_close(luaInterface);
        return;
    }
    if(!getContracts().isEmpty()){
        //result = setDeployBoss(name+"?10000?"+curTotal+"?"+codeCost,key);
        if(_doMethodW(getContract("0"),"_setDeployBoss",name+"?10000?"+curTotal+"?"+codeCost,key,result)){
            BUG << "setDeployBoss ok";
            setBoss(name.toLatin1(),result.toLatin1());
        }else{
            BUG << "setDeployBoss fail" << result;
            lua_close(luaInterface);
            return;
        }
    }
    if(flagStart && !resultInit.isEmpty() && resultInit != "null"){
        BUG << "doBroadcastAppNew" << resultInit;
        emit doBroadcastAppNew(resultInit.toLatin1());
    }
    emit doSetBossList(getBossAddressList());
    addContract(name.toLatin1(),luaInterface);
    insertBlock("0",curBlock);
    insertBlock(name.toLatin1(),curBlock);
    emit doDeployOldOK(name.toLatin1(),pData);
}
void onnObject::onMethodOld(QByteArray pData){
    onnBlock curBlock = createBlock(pData);
    if(flagStart){
        QByteArray curHash = GETSHA256(curBlock.blockData);
        if(getDatabaseBlock(curHash) != "null"){
            BUG << "bad method old: hash data exist" << curHash;
            return;
        }else{
            setDatabaseBlock(curHash,curHash);
        }
    }
    QList<QByteArray> pList = curBlock.blockData.split('$');
    QString name = pList.at(2);
    QString code = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    QString result;
    if(!checkBlockIndexAndHash(name,curBlock)){
        return;
    }
    if(_doMethodW(getContract(name.toLatin1()),code,arg,key,result)){
        insertBlock(name.toLatin1(),curBlock);
        emit doMethodOldOK(name.toLatin1(),pData);
        if(flagStart){
            if(!result.isEmpty() && result != "null"){
                emit doBroadcastAppNew(result.toLatin1());
            }
        }else{
            if(!result.isEmpty() && result != "null"){
                emit doBroadcastAppOld(result.toLatin1());
            }
        }
    }
}
void onnObject::onPeerOld(QByteArray pData){
    //BUG << pData;
    onnBlock curBlock = createBlock(pData);
    if(flagStart){
        QByteArray curHash = GETSHA256(curBlock.blockData);
        if(getDatabaseBlock(curHash) != "null"){
            BUG << "bad peer old: hash data exist" << curHash;
            return;
        }else{
            setDatabaseBlock(curHash,curHash);
        }
    }
    if(!checkBlockIndexAndHash("0",curBlock)){
        return;
    }
    QList<QByteArray> pList = curBlock.blockData.split('$');
    QByteArray arg = QByteArray::fromHex(pList.at(4));
    if(arg.contains('?')){
        QByteArrayList argList = arg.split('?');
        setPeerList(QString(argList.at(0)).split(","));
        setPeerLose(QString(argList.at(1)).split(","));
    }else{
        setPeerList(QString(arg).split(","));
    }
    setPeers();
    QByteArrayList curContractList = getBossMissingContracts();
    if(!curContractList.isEmpty())
        onBossMissing(curContractList);
    insertBlock("0",curBlock);
    emit doPeerOldOK(pData);
}
QStringList onnObject::getReadableContract(){
    return onnReadableContract;
}
bool onnObject::doFinishReadable(QString pContract){
    onnReadableContract.removeAll(pContract);
    QString curReadableContract;
    onnBlock prvBlock;
    onnBlock curBlock;
    QByteArray curValue;
    if(onnReadableContract.isEmpty()){
        flagStart = true;
        emit doStartFinish();
        return true;
    }else{
        while(!onnReadableContract.isEmpty()){
            onnBossBlock curBossBlock = getBossBlock(onnReadableContract.first());
            curReadableContract = curBossBlock.name;
            prvBlock = curBossBlock.blockDeploy;
            curValue = getDatabaseBlock(curBossBlock.name+"-"+QByteArray::number(prvBlock.blockIndex.toLongLong()+1));
            if(curValue == "null"){
                onnReadableContract.removeAll(curBossBlock.name);
            }else{
                curBlock = createBlock(curValue);
                break;
            }
        }
        if(onnReadableContract.isEmpty()){
            flagStart = true;
            emit doStartFinish();
            return true;
        }
    }
    if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
        BUG << curReadableContract << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
        return doFinishReadable(curReadableContract);
    }
    if(curBlock.blockHashPrev!=prvBlock.blockHash){
        BUG << curReadableContract << "curBlock.blockHashPrev!=prvBlock.blockHash";
        return doFinishReadable(curReadableContract);
    }
    emit doBlockOld(curValue);
    return false;
}
void onnObject::onPeerOldOK(QByteArray pData){
    onnBlock curBlock1 = createBlock(pData);
    if(getDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex)=="null"){
        setDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex,pData);
    }
    BUG << curBlock1.blockIndex;
    if(flagStart){
        return;
    }
    qint64 i = curBlock1.blockIndex.toLongLong()+1;
    QByteArray curKey = "0-";
    QByteArray prvValue = pData;
    QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
    if(i==1){
        prvValue = getBlock0();
    }
    onnBlock curBlock;
    onnBlock prvBlock;
    if(curValue == "null"){
        doFinishReadable("0");
        return;
    }else{
        curBlock = createBlock(curValue);
        prvBlock = createBlock(prvValue);
    }
    if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
        BUG << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
        doFinishReadable("0");
        return;
    }
    if(curBlock.blockHashPrev!=prvBlock.blockHash){
        BUG << "curBlock.blockHashPrev!=prvBlock.blockHash";
        doFinishReadable("0");
        return;
    }
    emit doBlockOld(curValue);
}
void onnObject::onDeployOldOK(QByteArray pContract,QByteArray pData){
    onnBlock curBlock1 = createBlock(pData);
    if(getDatabaseBlock(pContract+"-"+curBlock1.blockIndex)=="null"){
        setDatabaseBlock(pContract+"-"+curBlock1.blockIndex,pData);
    }
    if(getDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex)=="null"){
        setDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex,pData);
    }
    BUG << pContract << curBlock1.blockIndex;
    if(flagStart){
        return;
    }
    qint64 i = curBlock1.blockIndex.toLongLong()+1;
    QByteArray curKey = "0-";
    QByteArray prvValue = pData;
    QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
    if(i==1){
        prvValue = getBlock0();
    }
    if(curValue == "null"){
        doFinishReadable("0");
        return;
    }
    onnBlock curBlock = createBlock(curValue);
    onnBlock prvBlock = createBlock(prvValue);
    if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
        BUG << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
        doFinishReadable("0");
        return;
    }
    if(curBlock.blockHashPrev!=prvBlock.blockHash){
        BUG << "curBlock.blockHashPrev!=prvBlock.blockHash";
        doFinishReadable("0");
        return;
    }
    emit doBlockOld(curValue);
}
void onnObject::onMethodOldOK(QByteArray pContract,QByteArray pData){
    onnBlock curBlock1 = createBlock(pData);
    if(getDatabaseBlock(pContract+"-"+curBlock1.blockIndex)=="null"){
        setDatabaseBlock(pContract+"-"+curBlock1.blockIndex,pData);
    }
    BUG << pContract << curBlock1.blockIndex;
    if(flagStart){
        return;
    }
    qint64 i = curBlock1.blockIndex.toLongLong()+1;
    QByteArray curKey = pContract+"-";
    QByteArray prvValue = pData;
    QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
    if(i==1){
        prvValue = getBlock0();
    }
    if(curValue == "null"){
        doFinishReadable(pContract);
        return;
    }
    onnBlock curBlock = createBlock(curValue);
    onnBlock prvBlock = createBlock(prvValue);
    if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
        BUG << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
        doFinishReadable(pContract);
        return;
    }
    if(curBlock.blockHashPrev!=prvBlock.blockHash){
        BUG << "curBlock.blockHashPrev!=prvBlock.blockHash";
        doFinishReadable(pContract);
        return;
    }
    emit doBlockOld(curValue);
}
void onnObject::onDestroyOldOK(QByteArray pData){
    onnBlock curBlock1 = createBlock(pData);
    if(getDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex)=="null"){
        setDatabaseBlock(QByteArray("0-")+curBlock1.blockIndex,pData);
    }
    BUG << curBlock1.blockIndex;
    if(flagStart){
        return;
    }
    qint64 i = curBlock1.blockIndex.toLongLong()+1;
    QByteArray curKey = "0-";
    QByteArray prvValue = pData;
    QByteArray curValue = getDatabaseBlock(curKey+QByteArray::number(i));
    if(i==1){
        prvValue = getBlock0();
    }
    if(curValue == "null"){
        doFinishReadable("0");
        return;
    }
    onnBlock curBlock = createBlock(curValue);
    onnBlock prvBlock = createBlock(prvValue);
    if(curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1){
        BUG << "curBlock.blockIndex.toLongLong()!=prvBlock.blockIndex.toLongLong()+1";
        doFinishReadable("0");
        return;
    }
    if(curBlock.blockHashPrev!=prvBlock.blockHash){
        BUG << "curBlock.blockHashPrev!=prvBlock.blockHash";
        doFinishReadable("0");
        return;
    }
    emit doBlockOld(curValue);
}

void onnObject::onBlockNew(QByteArray pData){
    QList<QByteArray> listCmd = pData.split('&');
    if(listCmd.count()<2){
        BUG << "bad data: listCmd.count()<2" << pData;
        return;
    }
    QByteArray sign = listCmd.at(0);
    QByteArray data = listCmd.at(1);
    QList<QByteArray> listData = data.split('$');
    if(listData.count()<5){
        BUG << "bad data: listData.count()<5" << pData;
        return;
    }

    QByteArray type = listData.at(0);
    QByteArray pubkey = listData.at(1);
    QByteArray name = listData.at(2);
    QByteArray code = listData.at(3);
    QByteArray arg = QByteArray::fromHex(listData.at(4));

/*
    QByteArray curIdentityPubkey = GETADDR(getIdentity(name).toLatin1());
    if(curIdentityPubkey != onnObjectKey.address){
        BUG << "send to boss" << name;
        emit doSendBlockChainData(name,curIdentityPubkey,pData);
        return;
    }
*/
    if(code == "init"){
        BUG << "bad block new: can not call init" << name;
        return;
    }
    if(!getVerify(pubkey,data,sign)){
        BUG << "msg fail: verify fail" << pData;
        return;
    }

    if(type == "deploy"){
        if(hasContract(name)){
            BUG << "bad deploy: contract exist" << name;
            return;
        }
        emit doDeployNew(pData);
    }else if(type == "method"){
        if(code.left(3) == "get" || code.left(1) == "_"){
            BUG << "bad method: can not run private or get" << code ;
            return;
        }
        emit doMethodNew(pData);
    }else if(type == "peer"){
        if(name != "0"){
            BUG << "bad deploy: only 0 can update peer" << name;
            return;
        }
        emit doPeerNew(pData);
    }else if(type == "destroy"){
        if(!hasContract(name)){
            BUG << "bad destroy: contract not exist" << name;
            return;
        }
        emit doDestroyNew(pData);
    }else{
        BUG << "Unknow" << name << type;
    }
}
void onnObject::onDestroyNew(QByteArray pData){
    QByteArray curHash = GETSHA256(pData);
    if(getDatabaseBlock(curHash) != "null"){
        BUG << "bad destroy: hash data exist" << curHash;
        return;
    }
    QList<QByteArray> pList = pData.split('$');
    QString name = pList.at(2);
    QString codeHex = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    if(!hasContract(name.toLatin1())){
        BUG << "bad destroy: contract not exist" << name;
        return;
    }
    if(getBoss("0") != onnObjectKey.address){
        BUG << "send to boss 0" << getBoss("0");
        emit doCustomRequire(name,getBoss("0"),"newblock",pData);
        return;
    }
    if(!doOnnDestroy(name,key)){
        BUG << "doOnnDestroy fail";
        return;
    }
    lua_State *curContract = getContract(arg.toLatin1());
    lua_close(curContract);
    onnObjectContract->remove(arg);
    rmBoss(arg.toLatin1());
    onnBlock curBlock = createBlock(getBlock("0").blockIndex.toLongLong()+1,\
                                    QDateTime::currentMSecsSinceEpoch(),\
                                    getBlock("0").blockHash,\
                                    pData);
    insertBlock("0",curBlock);
    setDatabaseBlock(curHash,curHash);
    emit doDestroyNewOK(toString(curBlock));
}
void onnObject::onDeployNew(QByteArray pData){
    if(!getBossMissing(getPeerList()).isEmpty()){
        BUG << "bad deploy: an contract boss is missing" << getBossMissing(getPeerList());
        return;
    }
    QByteArray curHash = GETSHA256(pData);
    if(getDatabaseBlock(curHash) != "null"){
        BUG << "bad deploy: hash data exist" << curHash;
        return;
    }
    QList<QByteArray> pList = pData.split('$');
    QString name = pList.at(2);
    QString codeHex = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    if(hasContract(name.toLatin1())){
        BUG << "bad deploy: contract exist" << name;
        return;
    }
    if(getBoss("0") != onnObjectKey.address){
        BUG << "send to boss" << name << getBoss("0");
        emit doCustomRequire(name,getBoss("0"),"newblock",pData);
        return;
    }
    QString code;
    if(codeHex.contains("i")){
        code = codeHex;
    }else{
        code = QByteArray::fromHex(codeHex.toLatin1());
    }
    if(code.contains("_G")){
        BUG << "bad deploy: contains _G" << name;
        return;
    }
    /*
    if(code.contains("require")){
        BUG << "bad deploy: contains require" << name;
        return;
    }
    */
    if(hasSyncQueueRequest("0")){
        BUG << "bad deploy: hasSyncQueueRequest 0";
        return;
    }
    QString codeCost = QString::number(code.count()*2);
    //code.push_front(contractHead);
    lua_State *luaInterface = luaL_newstate();
    luaL_openlibs1(luaInterface);
    luaL_dostring(luaInterface,code.toLatin1().data());
    QString result;
    QString resultInit;
    if(!_doMethodW(luaInterface,"init",arg,key,resultInit)){
        lua_close(luaInterface);
        return;
    }
    QString curTotal;
    if(_doMethodR(luaInterface,"_getTotal","null",onnObjectKey.address,result)){
        curTotal = result;
    }else{
        curTotal = "0";
    }
    if(curTotal == "0"){
        lua_close(luaInterface);
        return;
    }
    result = setDeployBoss(name+"?10000?"+curTotal+"?"+codeCost,key);
    if(result == "fail"){
        BUG << "setDeployBoss fail";
        lua_close(luaInterface);
        return;
    }else{
        BUG << "setDeployBoss ok";
        setBoss(name.toLatin1(),result.toLatin1());
    }
    if(!resultInit.isEmpty() && resultInit != "null"){
        BUG << "doBroadcastAppNew" << resultInit;
        emit doBroadcastAppNew(resultInit.toLatin1());
    }
    emit doSetBossList(getBossAddressList());
    addContract(name.toLatin1(),luaInterface);
    onnBlock curBlock = createBlock(getBlock("0").blockIndex.toLongLong()+1,\
                                    QDateTime::currentMSecsSinceEpoch(),\
                                    getBlock("0").blockHash,\
                                    pData);
    insertBlock("0",curBlock);
    insertBlock(name.toLatin1(),curBlock);
    setDatabaseBlock(curHash,curHash);
    emit doDeployNewOK(name.toLatin1(),toString(curBlock));
}
void onnObject::onMethodNew(QByteArray pData){
    QByteArray curHash = GETSHA256(pData);
    if(getDatabaseBlock(curHash) != "null"){
        BUG << "bad method: hash data exist" << curHash;
        return;
    }
    QList<QByteArray> pList = pData.split('$');
    QString name = pList.at(2);
    QString code = pList.at(3);
    QString arg = QByteArray::fromHex(pList.at(4));
    QString key = GETADDR(pList.at(1));
    QString result;
    if(name == "0" && code == "transfer" && !getBossMissing(getPeerList()).isEmpty()){
        BUG << "bad method: an contract boss is missing" << getBossMissing(getPeerList());
        return;
    }
    if(!checkBlockNewIdentity(name,pData)){
        return;
    }
    if(hasSyncQueueRequest(name.toLatin1())){
        BUG << "bad method: hasSyncQueueRequest" << name;
        return;
    }
    if(_doMethodW(getContract(name.toLatin1()),code,arg,key,result)){
        onnBlock curBlock = createBlock(getBlock(name.toLatin1()).blockIndex.toLongLong()+1,\
                                        QDateTime::currentMSecsSinceEpoch(),\
                                        getBlock(name.toLatin1()).blockHash,\
                                        pData);
        insertBlock(name.toLatin1(),curBlock);
        emit doMethodNewOK(name.toLatin1(),toString(curBlock));
        if(!result.isEmpty() && result != "null"){
            BUG << "doBroadcastAppNew" << result;
            emit doBroadcastAppNew(result.toLatin1());
        }
        setDatabaseBlock(curHash,curHash);
    }
}
void onnObject::onPeerNew(QByteArray pData){
    QByteArray curHash = GETSHA256(pData);
    if(getDatabaseBlock(curHash) != "null"){
        BUG << "bad peer: hash data exist" << curHash;
        return;
    }
    if(!getPeerList().isEmpty() && !getBossMissing(getPeerList()).isEmpty()){
        BUG << "bad peer: an contract boss is missing" << getBossMissing(getPeerList());
        return;
    }
    QList<QByteArray> pList = pData.split('$');
    QString arg = QByteArray::fromHex(pList.at(4));
    if(!checkBlockNewIdentity("0",pData)){
        return;
    }
    if(hasSyncQueueRequest("0")){
        BUG << "bad peers: hasSyncQueueRequest";
        return;
    }
    if(arg.contains("?")){
        QStringList argList = arg.split("?");
        if(getPeerList().join(",")==argList.at(1)){
            return;
        }
        setPeerList(argList.at(0).split(","));
        setPeerLose(argList.at(1).split(","));
    }else{
        if(getPeerList().join(",")==arg){
            return;
        }
        setPeerList(arg.split(","));
    }
    setPeers();
    QByteArrayList curContractList = getBossMissingContracts();
    if(!curContractList.isEmpty())
        onBossMissing(curContractList);
    onnBlock curBlock = createBlock(getBlock("0").blockIndex.toLongLong()+1,\
                                    QDateTime::currentMSecsSinceEpoch(),\
                                    getBlock("0").blockHash,\
                                    pData);
    insertBlock("0",curBlock);
    setDatabaseBlock(curHash,curHash);
    emit doPeerNewOK(toString(curBlock));
}
void onnObject::onPeerNewOK(QByteArray pData){
    //BUG << pData;
    onnBlock curBlock = createBlock(pData);
    setDatabaseBlock(QByteArray("0-")+curBlock.blockIndex,pData);
    //emit doBoardcastBlockChainLevel("0",onnObject::toString(curBlock));
    BUG << curBlock.blockIndex;
}
void onnObject::onDeployNewOK(QByteArray pContract,QByteArray pData){
    onnBlock curBlock = createBlock(pData);
    setDatabaseBlock(QByteArray("0-")+curBlock.blockIndex,pData);
    setDatabaseBlock(pContract+'-'+curBlock.blockIndex,pData);
    //emit doBoardcastBlockChainLevel("0",onnObject::toString(curBlock));
    BUG << pContract << curBlock.blockIndex;
}
void onnObject::onMethodNewOK(QByteArray pContract,QByteArray pData){
    if(!hasBlock(pContract)){
        BUG << "ERROR: contract not exist" << pContract;
        exit(-1);
    }
    onnBlock curBlock = createBlock(pData);
    setDatabaseBlock(pContract+'-'+curBlock.blockIndex,pData);
    //emit doBoardcastBlockChainLevel(pContract,onnObject::toString(curBlock));
    BUG << pContract << curBlock.blockIndex;
}
void onnObject::onDestroyNewOK(QByteArray pData){
    onnBlock curBlock = createBlock(pData);
    setDatabaseBlock(QByteArray("0-")+curBlock.blockIndex,pData);
    //emit doBoardcastBlockChainLevel(pContract,onnObject::toString(curBlock));
    BUG << curBlock.blockIndex;
}

void onnObject::onSaveBlock(QByteArray,QByteArray){}

void onnObject::onBlockOldFinish(){}

void onnObject::onUdpdPeer(QStringList pList, QStringList pLose, QStringList pNew){
    if(flagStart == false){
        BUG << "fail: flagStart == false";
        return;
    }else{
        if(pList.isEmpty()){
            BUG << "fail: pList.count()==0";
            return;
        }
        pList.append(onnObjectKey.address);
        emit doSetBossList(getBossAddressList());
    }
    if(!pLose.isEmpty()){
        rmSyncLose(pLose);
    }
    setUdpClientList(pList);
    //pList = getHaveBalanceWorker0(pList,10000);
    BUG;
    BUG << "list" << pList;
    BUG << "lose" << pLose;
    BUG << "new " << pNew;
    //for test disable
    if(!pList.isEmpty() && pList != getPeerList()){
        if(getBoss("0") == onnObjectKey.address){
            QByteArray curData;
            if(pLose.isEmpty())
                curData = doCustomSet("peer","0","peer",(pList.join(",")).toLatin1().toHex());
            else
                curData = doCustomSet("peer","0","peer",(pList.join(",")+"?"+pLose.join(",")).toLatin1().toHex());
            //emit doBlockNew(curData);
            QtConcurrent::run(QThreadPool::globalInstance(),this,&onnObject::onBlockNew,curData);
        }
    }
}
void onnObject::onBroadcastBlockChainLevel(QString pContract, QString pAddress, QString pIndex){
    //BUG << pContract << pAddress;
    if(!hasUdpClientList(pAddress)){
        BUG << "!hasUdpClientList(pAddress)";
        return;
    }/*
    onnBlock curBlock = createBlock(pData.toLatin1());
    if(curBlock.blockIndex.isEmpty()){
        BUG << "curBlock.blockIndex.isEmpty()";
        return;
    }*/
    if(pContract == "0" && pIndex == "0"){
        BUG << "pContract == 0 && pIndex == 0";
        return;
    }
    if(!hasBlock(pContract.toLatin1())){
        //emit doRequireBlockChainData(pContract,curBlock.blockMaker,0,curBlock.blockIndex);
        BUG << "!hasBlock(pContract.toLatin1())";
        return;
    }
    onnBlock localBlock = getBlock(pContract);

    if(pIndex.toLongLong()<=localBlock.blockIndex.toLongLong()){
        //BUG << "pIndex.toLongLong()<=localBlock.blockIndex.toLongLong()" << pIndex << localBlock.blockIndex;
        return;
    }/*else if(curBlock.blockIndex.toLongLong()==localBlock.blockIndex.toLongLong()+1){
        emit doBlockOld(pData.toLatin1());
        return;
    }
    */
    if(!hasSyncQueue(pContract.toLatin1(),pAddress.toLatin1(),"request")){
        BUG << "doRequireBlockChainData" << localBlock.blockIndex.toLongLong()+1 << pIndex;
        //emit doRequireBlockChainData(pContract,pAddress,QString::number(localBlock.blockIndex.toLongLong()+1),curBlock.blockIndex);
        emit doCustomRequire(pContract,pAddress.toLatin1(),"require",QString::number(localBlock.blockIndex.toLongLong()+1)+":"+pIndex);
        setSyncQueue(pContract.toLatin1(),pAddress.toLatin1(),"request",QString::number(localBlock.blockIndex.toLongLong()+1).toLatin1(),pIndex.toLatin1());
    }
}
void onnObject::onRequireBlockChainData(QString pContract, QString nodeAddress, QString start, QString end){
    BUG << pContract << nodeAddress << start << end;
    if(!hasBlock(pContract.toLatin1())){
        BUG << "msg fail: !hasBlock(pContract)" << pContract;
        return;
    }
    if(start.toLongLong()<0 || end.toLongLong()<0){
        BUG << "msg fail: start.toLongLong()<0 || end.toLongLong()<0" << start << end;
        return;
    }
    if(start.toLongLong()>end.toLongLong()){
        BUG << "msg fail: start.toLongLong()<=end.toLongLong()" << start << end;
        return;
    }
    QByteArray curStartKey = pContract.toLatin1()+"-"+start.toLatin1();
    QByteArray curEndKey   = pContract.toLatin1()+"-"+end.toLatin1();
    if(getDatabaseBlock(curStartKey) == "null"){
        BUG << "msg fail: getDatabaseBlock(curStartKey) == null" << curStartKey;
        return;
    }
    if(getDatabaseBlock(curEndKey) == "null"){
        BUG << "msg fail: getDatabaseBlock(curEndKey) == null" << curEndKey;
        return;
    }
    quint32 curSize = 0;
    QJsonArray curArray;
    QJsonDocument curDocument;
    QByteArray curKey,curVar;
    for(qint64 i=start.toLongLong();i<=end.toLongLong() && curSize<8800;i++){
        curKey = pContract.toLatin1()+"-"+QString::number(i).toLatin1();
        curVar = getDatabaseBlock(curKey);
        curSize += curVar.count();
        curArray.append(QString(curVar));
    }
    BUG << "doSendBlockChainData" << curArray.size() << start << end;
    onnBlock curBlock = createBlock(curVar);
    curDocument.setArray(curArray);
    //emit doSendBlockChainData(pContract,nodeAddress,curDocument.toJson());
    emit doCustomRequire(pContract,nodeAddress.toLatin1(),"send",curDocument.toJson());
    if(!hasSyncQueue(pContract.toLatin1(),nodeAddress.toLatin1(),"response")){
        setSyncQueue(pContract.toLatin1(),nodeAddress.toLatin1(),"response",curBlock.blockIndex,end.toLatin1());
    }
    if(!updSyncQueueIndex(pContract.toLatin1(),nodeAddress.toLatin1(),"response",curBlock.blockIndex)){
        BUG << "rmSyncQueue response" <<  pContract;
        rmSyncQueue(pContract.toLatin1(),nodeAddress.toLatin1(),"response");
    }
}
void onnObject::onSendBlockChainData(QString pContract, QString pAddress, QString pData){
    BUG << pContract << pAddress << pData.count();
    QJsonDocument curDocument = QJsonDocument::fromJson(pData.toLatin1());
    QJsonArray curArray = curDocument.array();
    if(curArray.isEmpty()){
        return;
    }
    for(auto curData:curArray)
        emit doBlockOld(curData.toString().toLatin1());
    QByteArray lastBlock = curArray.last().toString().toLatin1();
    onnBlock curBlock = createBlock(lastBlock);
    if(curBlock.blockIndex.isEmpty()){
        return;
    }
    if(hasSyncQueue(pContract.toLatin1(),pAddress.toLatin1(),"request")){
        if(!updSyncQueueIndex(pContract.toLatin1(),pAddress.toLatin1(),"request",curBlock.blockIndex)){
            BUG << "rmSyncQueue request" <<  pContract;
            rmSyncQueue(pContract.toLatin1(),pAddress.toLatin1(),"request");
        }
    }
}


void onnObject::onCustomRequire(QString contractID, QString addr, QString cmd, QString data){
    if(flagStart == false){
        BUG << "fail: falg == false";
        return;
    }
    //BUG << cmd;
    if(cmd=="newblock"){
        //emit doBlockNew(data.toLatin1());
        QtConcurrent::run(QThreadPool::globalInstance(),this,&onnObject::onBlockNew,data.toLatin1());
    }else if(cmd=="level"){
        QStringList levelData = data.split(",");
        for(auto curLevel:levelData){
            QStringList curData = curLevel.split(":");
            if(curData.count() != 2){
                BUG << "error: data error" << curData;
                continue;
            }
            onBroadcastBlockChainLevel(curData.first(),addr,curData.last());
        }
    }else if(cmd=="require"){
        QStringList startEnd = data.split(":");
        if(startEnd.count()<2){
            BUG << cmd << "fail: startEnd.count()<2" << data;
            return;
        }
        onRequireBlockChainData(contractID,addr,startEnd.at(0),startEnd.at(1));
    }else if(cmd=="send"){
        onSendBlockChainData(contractID,addr,data);
    }else{
        BUG << "fail: Unknow cmd" << cmd;
    }
}

void onnObject::onBossMissing(QByteArrayList pList){
    for(auto curContract:pList){
        if(curContract=="0")
            continue;
        QString curResult = setNextBoss(curContract+"?10000");

        if(curResult == "fail"){
            BUG << "fail: _setNextBoss fail" << curContract << curResult;
        }else{
            BUG << "fail: _setNextBoss ok" << curContract << curResult;
            setBoss(curContract,curResult.toLatin1());
        }
    }
}

void onnObject::onTimeout(){
    if(!flagStart){
        BUG << "fail: flagStart == false";
        return;
    }
    if(getUdpClientList().isEmpty()){
        BUG << "fail: pList.isEmpty()";
        return;
    }
    QStringList curPeerList = getUdpClientList();
    if(curPeerList.count() == 1 && curPeerList.first() == onnObjectKey.address){
        BUG << "fail: curPeerList.count() == 1 && ==" << onnObjectKey.address;
        return;
    }
    QStringList levelData;
    QHash<QString,onnBossBlock> curBlockChain = *onnBlockChain;
    QHash<QString,onnBossBlock> *curBlockChainPtr = &curBlockChain;
    for(auto curBlockIter=curBlockChainPtr->begin();curBlockIter!=curBlockChainPtr->end();curBlockIter++){
        //BUG << "doBroadcastBlockChainLevel" << curBlockIter.key() << curBlockIter.value().blockCurrent.blockIndex;
        //emit doCustomBroadcast(curBlockIter.key(),"level",curBlockIter.value().blockCurrent.blockIndex);
        if(levelData.isEmpty()){
            levelData.append(curBlockIter.key()+":"+curBlockIter.value().blockCurrent.blockIndex);
        }else{
            if(levelData.last().count()>10000){
                levelData.append(curBlockIter.key()+":"+curBlockIter.value().blockCurrent.blockIndex);
            }else{
                levelData.replace(levelData.count()-1,levelData.last()+","+curBlockIter.key()+":"+curBlockIter.value().blockCurrent.blockIndex);
            }
        }
    }
    for(auto curLevel:levelData){
        emit doCustomBroadcast("*","level",curLevel);
    }
    QList<onnSyncQueue> curRemove;
    for(auto cur=onnSyncRequest.begin();cur!=onnSyncRequest.end();cur++){
        onnSyncQueue curData;
        if(!hasSyncQueue(cur.value().blockContract,cur.value().blockAddress,"request")){
            continue;
        }
        if(onnBlackList.contains(cur.value().blockAddress)){
            curRemove.append(getSyncQueue(cur.value().blockContract,cur.value().blockAddress,"request"));
            //rmSyncQueue(cur.value().blockContract,cur.value().blockAddress,"request");
            continue;
        }
        curData = getSyncQueue(cur.value().blockContract,cur.value().blockAddress,"request");
        if(QDateTime::currentMSecsSinceEpoch()-curData.blockLastModify>60*1000){
            curRemove.append(curData);
            //rmSyncQueue(cur.value().blockContract,cur.value().blockAddress,"request");
            onnBlackList.append(cur.value().blockAddress);
            //emit doRequireBlockChainData(cur.value().blockContract,cur.value().blockAddress,curData.blockCurrentIndex,curData.blockEnd);
        }
    }
    for(auto cur:curRemove){
        rmSyncQueue(cur.blockContract,cur.blockAddress,"request");
    }
    if(curRemove.count()>0)
        BUG << "curRemove Sync request =" << curRemove.count();
    curRemove.clear();
    QList<onnSyncQueue> curSyncQueue;
    for(auto cur=onnSyncResponse.begin();cur!=onnSyncResponse.end();cur++){
        if(!hasSyncQueue(cur.value().blockContract,cur.value().blockAddress,"response")){
            continue;
        }
        onnSyncQueue curQueue = getSyncQueue(cur.value().blockContract,cur.value().blockAddress,"response");
        quint32 curSize = 0;
        QJsonArray curArray;
        QJsonDocument curDocument;
        QByteArray curKey,curVar;
        for(qint64 i=curQueue.blockCurrentIndex.toLongLong();i<=curQueue.blockEnd.toLongLong() && curSize<88000;i++){
            curKey = cur.value().blockContract+"-"+QString::number(i).toLatin1();
            curVar = getDatabaseBlock(curKey);
            curSize += curVar.count();
            curArray.append(QString(curVar));
        }
        if(curSize>100000 && curArray.count()>1){
            curSize -= curArray.last().toString().count();
            curArray.removeLast();
            curVar = curArray.last().toString().toLatin1();
        }
        onnBlock curBlock = createBlock(curVar);
        BUG << curBlock.blockIndex;
        curDocument.setArray(curArray);
        //emit doSendBlockChainData(cur.value().blockContract,cur.value().blockAddress,curDocument.toJson());
        emit doCustomRequire(cur.value().blockContract,cur.value().blockAddress,"send",curDocument.toJson());
        if(!updSyncQueueIndex(cur.value().blockContract,cur.value().blockAddress,"response",curBlock.blockIndex)){
            curSyncQueue.append(curQueue);
        }
    }
    for(auto cur:curSyncQueue){
        rmSyncQueue(cur.blockContract,cur.blockAddress,"response");
    }
    if(curSyncQueue.count()>0)
        BUG << "curSyncQueue Sync response =" << curSyncQueue.count();
    if(!getBossAddressList().contains(onnObjectKey.address)){
        return;
    }
    if(getPeerList().isEmpty()){
        return;
    }
    //QStringList curBossLose = getBossLose(pLose);
    QByteArrayList curBossLose = getBossMissing(getPeerList());
    if(curBossLose.isEmpty()){
        return;
    }
    for(auto curBossAddress:curBossLose){
        rmBossFromAddress(curBossAddress);
    }
}
