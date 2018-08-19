#ifndef ONEDEFINE_H
#define ONEDEFINE_H

#include <QFile>
#include <QDebug>
#include <QMutex>
#include <iostream>
#include <QSettings>
#include <QtConcurrent>
#include <QThreadPool>
#include <QTcpServer>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUdpSocket>
#include <QDateTime>
#include <QNetworkDatagram>
#include <QMultiMap>
#include <cstdio>
#include <QMultiHash>
#include <QProcess>

#define BUG qDebug()<<__FILE__<< __LINE__ << __FUNCTION__
#define SETXF(A,B) QString("%1").arg(A, 0, 'f', B)

#define GETMD5(A) QCryptographicHash::hash(A,QCryptographicHash::Md5).toHex()
#define GETADDR(A) QCryptographicHash::hash(A,QCryptographicHash::Keccak_256).toHex().left(40)
#define GETSHA256(A) QCryptographicHash::hash(A,QCryptographicHash::Sha256).toHex()
#define GETPSD(A) GETSHA256(GETMD5(A))
#define CONN(A,B,C,D) QObject::connect(A,B,C,D,Qt::QueuedConnection)
#define DISC(A,B,C,D) QObject::disconnect(A,B,C,D)

struct onnKey {
    QByteArray appkey;
    QByteArray pubkey;
    QByteArray prikey;
    QByteArray address;
};

struct onnBlock {
    QByteArray blockIndex;
    QByteArray blockTimestamp;
    QByteArray blockHashPrev;
    QByteArray blockHash;
    QByteArray blockData;
    QByteArray blockMaker;
    QByteArray blockMakerSign;
};

struct onnBossBlock {
    QByteArray name;
    QByteArray owner;
    QByteArray total;
    QByteArray maker;
    QByteArray unuse;
    QByteArray rate;
    onnBlock blockDeploy;
    onnBlock blockCurrent;
};

struct onnData {
    QByteArray blockPubkey;
    QByteArray blockContract;
    QByteArray blockType;
    QByteArray blockTarget;
    onnBlock   block;
};

struct onnSyncQueue {
    QByteArray blockContract;
    QByteArray blockAddress;
    QByteArray blockStart;
    QByteArray blockEnd;
    QByteArray blockCurrentIndex;
    qint64     blockLastModify;
};
#endif // ONEDEFINE_H
