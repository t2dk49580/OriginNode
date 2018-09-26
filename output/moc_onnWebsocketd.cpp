/****************************************************************************
** Meta object code from reading C++ file 'onnWebsocketd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../onnWebsocketd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onnWebsocketd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_onnWebsocketd_t {
    QByteArrayData data[5];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_onnWebsocketd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_onnWebsocketd_t qt_meta_stringdata_onnWebsocketd = {
    {
QT_MOC_LITERAL(0, 0, 13), // "onnWebsocketd"
QT_MOC_LITERAL(1, 14, 7), // "onStart"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 17), // "onBroadcastAppNew"
QT_MOC_LITERAL(4, 41, 17) // "onBroadcastAppOld"

    },
    "onnWebsocketd\0onStart\0\0onBroadcastAppNew\0"
    "onBroadcastAppOld"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_onnWebsocketd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       4,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

       0        // eod
};

void onnWebsocketd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        onnWebsocketd *_t = static_cast<onnWebsocketd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onStart(); break;
        case 1: _t->onBroadcastAppNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->onBroadcastAppOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject onnWebsocketd::staticMetaObject = {
    { &onnObject::staticMetaObject, qt_meta_stringdata_onnWebsocketd.data,
      qt_meta_data_onnWebsocketd,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *onnWebsocketd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *onnWebsocketd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_onnWebsocketd.stringdata0))
        return static_cast<void*>(this);
    return onnObject::qt_metacast(_clname);
}

int onnWebsocketd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = onnObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
