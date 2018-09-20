#ifndef ONNOBJECT_H
#define ONNOBJECT_H

#include <QObject>
#include <leveldb/db.h>
//#include <lua5.3/lua.hpp>
#include "ovm/lua.hpp"
#include "onnDefine.h"
#include "ssl/num_openssl.h"
#include "ssl/field.h"
#include "ssl/group.h"
#include "ssl/ecmult.h"
#include "ssl/ecdsa.h"
#include <openssl/evp.h>
#include <openssl/x509.h>
#include "emcc/uECC.h"
#include "uws/uWS.h"
#include "netsync.h"

using namespace std;
using namespace uWS;
using namespace secp256k1;

class onnObject : public QObject
{
    Q_OBJECT
public:
    explicit onnObject(QString);
    virtual ~onnObject();

public:
    QString objType;

public:
    virtual void init();

    //加密函数
    static QByteArray Encrypt(QByteArray,QByteArray);
    //解密函数
    static QByteArray Decrypt(QByteArray,QByteArray);

    static QByteArray getBlock0();
    static void makeBlock0();

    static void initKey();
    static QByteArray computePubkey(QByteArray);
    static bool hasAppkey();
    static void updAppkey(QByteArray);
    static bool hasPubkey();
    static void makeKey(QByteArray);
    static QByteArray getSignature(QByteArray);
    static QByteArray getSignHash(QByteArray);
    static QByteArray getPubkey();
    static QByteArray getPrikey();
    static QByteArray getAddress();
    static QByteArray getHash(QByteArray);
    static bool getVerify(QByteArray,QByteArray,QByteArray);

    static QString getTaget(QString type,QString pubkey,QString name,QString code,QString arg,QString sig);
    static QString docmd(QString type,QString pubkey,QString prikey,QString name,QString func,QString arg);
    static QByteArray doMethodGet(QString pContract, QString pMethod, QString pArg);
    static QByteArray doMethodSet(QString pContract,QString pMethod,QString pArg);
    static QByteArray doCustomSet(QString pType,QString pContract,QString pMethod,QString pArg);
    static QByteArray doDeploy(QString pContract,QString pCode,QString pArg);
    static QByteArray doHandlerGet(QByteArray pData);

    static void initArgv(int argc, char *argv[]);
    static QString getArgument(QString);
    static QString getLocalIP();

    static void setPeerList(QStringList);
    static void setPeerLose(QStringList);
    static QStringList getPeerList();
    static QStringList getPeerLose();
    static QByteArray calcHash(onnBlock);
    static void setUdpClientList(QStringList);
    static QStringList getUdpClientList();
    static bool hasUdpClientList(QString);

    static void initDatabase();
    static QByteArray getDatabaseBlock(QByteArray);
    static bool setDatabaseBlock(QByteArray,QByteArray);

    static void insertBlock(QString,onnBlock);
    static onnBlock getBlock(QString);
    static onnBossBlock getBossBlock(QString);
    static QByteArray toString(onnBlock);
    static bool hasBlock(QByteArray);
    static onnBlock createBlock(QByteArray);
    static onnBlock createBlock(qint64,qint64,QString,QByteArray);

    static QString doGetRandom();
    static QString doGetRandom(int);
    static bool _doMethod (QString,QString,QString,QString,QString &);
    static bool _doMethod (lua_State *,QString,QString,QString,QString &);
    static bool _doMethodW(lua_State *,QString,QString,QString,QString &);
    static bool _doMethodR(lua_State *,QString,QString,QString,QString &);
    static QByteArray doMethodGet(QByteArray pMsg);

    static void addContract(QByteArray,lua_State *&);
    static bool hasContract(QByteArray);
    static lua_State *getContract(QByteArray);
    static QStringList getContracts();
    static QString getContractOrigin();
    static bool checkBlockIndexAndHash(QString,onnBlock);
    static bool checkBlockIndexAndHashDeploy(QString,onnBlock,onnBlock);
    bool checkBlockNewIdentity(QString,QByteArray);

    static void setBoss(QByteArray,QByteArray);
    static QByteArray getBoss(QByteArray);
    static void rmBoss(QByteArray);
    static void rmBossFromAddress(QByteArray);
    static QByteArrayList getBossFromAddress(QByteArray);
    static QByteArrayList getBossAddressList();
    static QStringList getBossLose(QStringList);
    static QByteArrayList getBossMissing(QStringList);
    static QByteArrayList getBossMissingContracts();
    static QStringList getOnlyWork(QStringList);

    static void initNetSync();
    static NetSync *getNetSync();

    static void initWebsocketd();
    static Hub *getWebsocketd();

    static void setSyncQueue(QByteArray,QByteArray,QByteArray,QByteArray,QByteArray);
    static bool updSyncQueueIndex(QByteArray,QByteArray,QByteArray,QByteArray);
    static onnSyncQueue getSyncQueue(QByteArray,QByteArray,QByteArray);
    static onnSyncQueue getSyncQueue(QStringList);
    static QList<onnSyncQueue> getSyncQueueList(QByteArray,QByteArray);
    static bool hasSyncQueueRequest(QByteArray);
    static bool hasSyncQueue(QByteArray,QByteArray,QByteArray);
    static void rmSyncQueue(QByteArray,QByteArray,QByteArray);
    static void rmSyncLose(QStringList);
    static int getSyncRequestCount();
    static int getSyncResponseCount();

    static void appendChangeBossRequest(QByteArray,QByteArray);
    static bool hasChangeBossRequest(QByteArray);
    static bool hasChangeBossWorkerRequest(QByteArray);
    static QByteArrayList getChangeBossRequest(QByteArray);
    static void rmChangeBossRequest(QByteArray);
    static double getContractBalance(QByteArray,QByteArray);
    static double getOnnBalance(QByteArray);
    static QByteArray getOnnBossOwner(QByteArray);
    static QByteArray getOnnBossTotal(QByteArray);
    static QByteArray getOnnBossMaker(QByteArray);
    static QByteArray setOnnBossMaker(QByteArray,QByteArray);
    static QString setNextBoss(QString);
    static QString setDeployBoss(QString,QString);
    static QString setPeers();
    static bool doOnnDestroy(QString,QString);
    static QByteArray doOnnTransfer(QByteArray,QByteArray,QByteArray);
    static bool checkCustomNetData(QByteArray,QByteArray,onnData &);
    static QMultiMap<qint64,QString> getOnnBalanceUserList(QStringList);
    static QStringList getHaveBalanceWorker0(QStringList,qint64);

    static QStringList getReadableContract();
    bool doFinishReadable(QString);

signals:
    void doInit();
    void doInitFinish();
    void doStart();
    void doStartFinish();

    void doBlockOld(QByteArray);
    void doDeployOld(QByteArray);
    void doMethodOld(QByteArray);
    void doPeerOld(QByteArray);
    void doDestroyOld(QByteArray);
    void doPeerOldOK(QByteArray);
    void doDeployOldOK(QByteArray,QByteArray);
    void doMethodOldOK(QByteArray,QByteArray);
    void doDestroyOldOK(QByteArray);

    void doBlockNew(QByteArray);
    void doDeployNew(QByteArray);
    void doMethodNew(QByteArray);
    void doPeerNew(QByteArray);
    void doDestroyNew(QByteArray);
    void doPeerNewOK(QByteArray);
    void doDeployNewOK(QByteArray,QByteArray);
    void doMethodNewOK(QByteArray,QByteArray);
    void doDestroyNewOK(QByteArray);

    void doSaveBlock(QByteArray,QByteArray);

    void doBlockOldFinish();

    void doBroadcastAppOld(QByteArray);
    void doBroadcastAppNew(QByteArray);

    void doUpdPeerNew(QStringList,QStringList);
    void doBroadcastBlockChainLevel(QString id, QString level);
    void doRequireBlockChainData(QString id, QString nodeAddress, QString start, QString end);
    void doSendBlockChainData(QString id, QString nodeAddress, QString data);

    void doSetBossList(QByteArrayList);
    void doCustomRequire(QString contractID, QByteArray addr, QString cmd, QString data);
    void doCustomBroadcast(QString contractID, QString cmd, QString data);

    void doBossMissing(QByteArrayList);

public:
    bool flagStart;
public slots:
    virtual void onInit();
    virtual void onInitFinish();
    virtual void onStart();
    virtual void onStartFinish();
    virtual void onTimeout();

    void onBlockOld(QByteArray);
    void onDeployOld(QByteArray);
    void onMethodOld(QByteArray);
    void onPeerOld(QByteArray);
    void onDestroyOld(QByteArray);
    void onPeerOldOK(QByteArray);
    void onDeployOldOK(QByteArray,QByteArray);
    void onMethodOldOK(QByteArray,QByteArray);
    void onDestroyOldOK(QByteArray);

    void onBlockNew(QByteArray);
    void onDeployNew(QByteArray);
    void onMethodNew(QByteArray);
    void onPeerNew(QByteArray);
    void onDestroyNew(QByteArray);
    void onPeerNewOK(QByteArray);
    void onDeployNewOK(QByteArray,QByteArray);
    void onMethodNewOK(QByteArray,QByteArray);
    void onDestroyNewOK(QByteArray);

    void onSaveBlock(QByteArray,QByteArray);

    void onBlockOldFinish();

    void onUdpdPeer(QStringList,QStringList,QStringList);
    void onBroadcastBlockChainLevel(QString, QString, QString);
    void onRequireBlockChainData(QString, QString, QString, QString);
    void onSendBlockChainData(QString, QString, QString);

    void onCustomRequire(QString contractID, QString addr, QString cmd, QString data);

    void onBossMissing(QByteArrayList);
};

#endif // ONNOBJECT_H
