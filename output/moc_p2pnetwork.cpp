/****************************************************************************
** Meta object code from reading C++ file 'p2pnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/p2p/p2pnetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'p2pnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_P2PNetwork_t {
    QByteArrayData data[13];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_P2PNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_P2PNetwork_t qt_meta_stringdata_P2PNetwork = {
    {
QT_MOC_LITERAL(0, 0, 10), // "P2PNetwork"
QT_MOC_LITERAL(1, 11, 16), // "UpdateMemberList"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "OnRcv"
QT_MOC_LITERAL(4, 35, 3), // "msg"
QT_MOC_LITERAL(5, 39, 12), // "QHostAddress"
QT_MOC_LITERAL(6, 52, 2), // "ip"
QT_MOC_LITERAL(7, 55, 4), // "port"
QT_MOC_LITERAL(8, 60, 11), // "OnBroadcast"
QT_MOC_LITERAL(9, 72, 4), // "addr"
QT_MOC_LITERAL(10, 77, 11), // "QIPEndPoint"
QT_MOC_LITERAL(11, 89, 8), // "endPoint"
QT_MOC_LITERAL(12, 98, 11) // "OnHeartbeat"

    },
    "P2PNetwork\0UpdateMemberList\0\0OnRcv\0"
    "msg\0QHostAddress\0ip\0port\0OnBroadcast\0"
    "addr\0QIPEndPoint\0endPoint\0OnHeartbeat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_P2PNetwork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   35,    2, 0x08 /* Private */,
       8,    3,   42,    2, 0x08 /* Private */,
      12,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5, QMetaType::UShort,    4,    6,    7,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 10, QMetaType::QString,    9,   11,    4,
    QMetaType::Void,

       0        // eod
};

void P2PNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        P2PNetwork *_t = static_cast<P2PNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateMemberList(); break;
        case 1: _t->OnRcv((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 2: _t->OnBroadcast((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QIPEndPoint(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->OnHeartbeat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (P2PNetwork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&P2PNetwork::UpdateMemberList)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject P2PNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_P2PNetwork.data,
      qt_meta_data_P2PNetwork,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *P2PNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *P2PNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_P2PNetwork.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int P2PNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void P2PNetwork::UpdateMemberList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
