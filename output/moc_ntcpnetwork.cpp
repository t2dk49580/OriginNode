/****************************************************************************
** Meta object code from reading C++ file 'ntcpnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/Network/ntcpnetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ntcpnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NTcpNetwork_t {
    QByteArrayData data[12];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NTcpNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NTcpNetwork_t qt_meta_stringdata_NTcpNetwork = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NTcpNetwork"
QT_MOC_LITERAL(1, 12, 12), // "ServerRcvMsg"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "msg"
QT_MOC_LITERAL(4, 30, 11), // "QTcpSocket*"
QT_MOC_LITERAL(5, 42, 6), // "sender"
QT_MOC_LITERAL(6, 49, 12), // "ClientRcvMsg"
QT_MOC_LITERAL(7, 62, 16), // "ClientDisconnect"
QT_MOC_LITERAL(8, 79, 12), // "OnNewConnect"
QT_MOC_LITERAL(9, 92, 18), // "OnClientDisconnect"
QT_MOC_LITERAL(10, 111, 14), // "OnServerRcvMsg"
QT_MOC_LITERAL(11, 126, 14) // "OnClientRcvMsg"

    },
    "NTcpNetwork\0ServerRcvMsg\0\0msg\0QTcpSocket*\0"
    "sender\0ClientRcvMsg\0ClientDisconnect\0"
    "OnNewConnect\0OnClientDisconnect\0"
    "OnServerRcvMsg\0OnClientRcvMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NTcpNetwork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       6,    1,   54,    2, 0x06 /* Public */,
       7,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NTcpNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NTcpNetwork *_t = static_cast<NTcpNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ServerRcvMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTcpSocket*(*)>(_a[2]))); break;
        case 1: _t->ClientRcvMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ClientDisconnect((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 3: _t->OnNewConnect(); break;
        case 4: _t->OnClientDisconnect(); break;
        case 5: _t->OnServerRcvMsg(); break;
        case 6: _t->OnClientRcvMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NTcpNetwork::*)(QString , QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NTcpNetwork::ServerRcvMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NTcpNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NTcpNetwork::ClientRcvMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NTcpNetwork::*)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NTcpNetwork::ClientDisconnect)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NTcpNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NTcpNetwork.data,
      qt_meta_data_NTcpNetwork,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NTcpNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NTcpNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NTcpNetwork.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NTcpNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void NTcpNetwork::ServerRcvMsg(QString _t1, QTcpSocket * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NTcpNetwork::ClientRcvMsg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NTcpNetwork::ClientDisconnect(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
