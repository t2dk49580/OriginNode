/****************************************************************************
** Meta object code from reading C++ file 'netsync.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../NetSync/netsync.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netsync.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetSync_t {
    QByteArrayData data[24];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetSync_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetSync_t qt_meta_stringdata_NetSync = {
    {
QT_MOC_LITERAL(0, 0, 7), // "NetSync"
QT_MOC_LITERAL(1, 8, 16), // "doUpdatePeerList"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "list"
QT_MOC_LITERAL(4, 31, 8), // "deadList"
QT_MOC_LITERAL(5, 40, 12), // "newComerList"
QT_MOC_LITERAL(6, 53, 11), // "doPeerState"
QT_MOC_LITERAL(7, 65, 9), // "livePeers"
QT_MOC_LITERAL(8, 75, 12), // "doOnnRequire"
QT_MOC_LITERAL(9, 88, 10), // "contractID"
QT_MOC_LITERAL(10, 99, 4), // "addr"
QT_MOC_LITERAL(11, 104, 3), // "cmd"
QT_MOC_LITERAL(12, 108, 4), // "data"
QT_MOC_LITERAL(13, 113, 13), // "onEnterSubNet"
QT_MOC_LITERAL(14, 127, 12), // "onQuitSubNet"
QT_MOC_LITERAL(15, 140, 13), // "onGetBossAddr"
QT_MOC_LITERAL(16, 154, 8), // "bossList"
QT_MOC_LITERAL(17, 163, 22), // "onQueuePeerStatebyAddr"
QT_MOC_LITERAL(18, 186, 8), // "peerList"
QT_MOC_LITERAL(19, 195, 12), // "onOnnRequire"
QT_MOC_LITERAL(20, 208, 14), // "onOnnBroadcast"
QT_MOC_LITERAL(21, 223, 9), // "RcvP2pMsg"
QT_MOC_LITERAL(22, 233, 3), // "msg"
QT_MOC_LITERAL(23, 237, 14) // "PeerListUpdate"

    },
    "NetSync\0doUpdatePeerList\0\0list\0deadList\0"
    "newComerList\0doPeerState\0livePeers\0"
    "doOnnRequire\0contractID\0addr\0cmd\0data\0"
    "onEnterSubNet\0onQuitSubNet\0onGetBossAddr\0"
    "bossList\0onQueuePeerStatebyAddr\0"
    "peerList\0onOnnRequire\0onOnnBroadcast\0"
    "RcvP2pMsg\0msg\0PeerListUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetSync[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,
       8,    4,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   88,    2, 0x0a /* Public */,
      14,    1,   91,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      17,    1,   97,    2, 0x0a /* Public */,
      19,    4,  100,    2, 0x0a /* Public */,
      20,    3,  109,    2, 0x0a /* Public */,
      21,    1,  116,    2, 0x08 /* Private */,
      23,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    3,    4,    5,
    QMetaType::Void, QMetaType::QByteArrayList,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   10,   11,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QByteArrayList,   16,
    QMetaType::Void, QMetaType::QByteArrayList,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QString, QMetaType::QString,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    9,   11,   12,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QStringList,    3,

       0        // eod
};

void NetSync::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetSync *_t = static_cast<NetSync *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doUpdatePeerList((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 1: _t->doPeerState((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        case 2: _t->doOnnRequire((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->onEnterSubNet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->onQuitSubNet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onGetBossAddr((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        case 6: _t->onQueuePeerStatebyAddr((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        case 7: _t->onOnnRequire((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 8: _t->onOnnBroadcast((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: _t->RcvP2pMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->PeerListUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetSync::*)(QStringList , QStringList , QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetSync::doUpdatePeerList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetSync::*)(QByteArrayList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetSync::doPeerState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetSync::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetSync::doOnnRequire)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetSync::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetSync.data,
      qt_meta_data_NetSync,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetSync::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetSync::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetSync.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetSync::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void NetSync::doUpdatePeerList(QStringList _t1, QStringList _t2, QStringList _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetSync::doPeerState(QByteArrayList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetSync::doOnnRequire(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
