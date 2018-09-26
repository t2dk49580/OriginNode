/****************************************************************************
** Meta object code from reading C++ file 'mainnetserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../NetSync/mainnetserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainnetserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainNetServer_t {
    QByteArrayData data[12];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainNetServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainNetServer_t qt_meta_stringdata_MainNetServer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainNetServer"
QT_MOC_LITERAL(1, 14, 13), // "P2PListUpdate"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "list"
QT_MOC_LITERAL(4, 34, 6), // "RcvMsg"
QT_MOC_LITERAL(5, 41, 3), // "msg"
QT_MOC_LITERAL(6, 45, 9), // "NodeState"
QT_MOC_LITERAL(7, 55, 11), // "OnServerMsg"
QT_MOC_LITERAL(8, 67, 3), // "cmd"
QT_MOC_LITERAL(9, 71, 3), // "dat"
QT_MOC_LITERAL(10, 75, 8), // "OnP2pMsg"
QT_MOC_LITERAL(11, 84, 6) // "OnJoin"

    },
    "MainNetServer\0P2PListUpdate\0\0list\0"
    "RcvMsg\0msg\0NodeState\0OnServerMsg\0cmd\0"
    "dat\0OnP2pMsg\0OnJoin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainNetServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   53,    2, 0x08 /* Private */,
      10,    1,   58,    2, 0x08 /* Private */,
      11,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QStringList,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void MainNetServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainNetServer *_t = static_cast<MainNetServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->P2PListUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->RcvMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->NodeState((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->OnServerMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->OnP2pMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->OnJoin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainNetServer::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainNetServer::P2PListUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainNetServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainNetServer::RcvMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainNetServer::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainNetServer::NodeState)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainNetServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MainNetServer.data,
      qt_meta_data_MainNetServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainNetServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainNetServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainNetServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MainNetServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MainNetServer::P2PListUpdate(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainNetServer::RcvMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainNetServer::NodeState(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
