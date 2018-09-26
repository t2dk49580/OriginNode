/****************************************************************************
** Meta object code from reading C++ file 'np2pringnet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/p2p/np2pringnet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'np2pringnet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NP2PRingNet_t {
    QByteArrayData data[7];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NP2PRingNet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NP2PRingNet_t qt_meta_stringdata_NP2PRingNet = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NP2PRingNet"
QT_MOC_LITERAL(1, 12, 4), // "Send"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "addr"
QT_MOC_LITERAL(4, 23, 11), // "QIPEndPoint"
QT_MOC_LITERAL(5, 35, 8), // "endPoint"
QT_MOC_LITERAL(6, 44, 3) // "msg"

    },
    "NP2PRingNet\0Send\0\0addr\0QIPEndPoint\0"
    "endPoint\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NP2PRingNet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4, QMetaType::QString,    3,    5,    6,

       0        // eod
};

void NP2PRingNet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NP2PRingNet *_t = static_cast<NP2PRingNet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Send((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QIPEndPoint(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NP2PRingNet::*)(QByteArray , QIPEndPoint , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NP2PRingNet::Send)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NP2PRingNet::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NP2PRingNet.data,
      qt_meta_data_NP2PRingNet,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NP2PRingNet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NP2PRingNet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NP2PRingNet.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NP2PRingNet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void NP2PRingNet::Send(QByteArray _t1, QIPEndPoint _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
