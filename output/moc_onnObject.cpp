/****************************************************************************
** Meta object code from reading C++ file 'onnObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../onnObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'onnObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_onnObject_t {
    QByteArrayData data[76];
    char stringdata0[967];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_onnObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_onnObject_t qt_meta_stringdata_onnObject = {
    {
QT_MOC_LITERAL(0, 0, 9), // "onnObject"
QT_MOC_LITERAL(1, 10, 6), // "doInit"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "doInitFinish"
QT_MOC_LITERAL(4, 31, 7), // "doStart"
QT_MOC_LITERAL(5, 39, 13), // "doStartFinish"
QT_MOC_LITERAL(6, 53, 10), // "doBlockOld"
QT_MOC_LITERAL(7, 64, 11), // "doDeployOld"
QT_MOC_LITERAL(8, 76, 11), // "doMethodOld"
QT_MOC_LITERAL(9, 88, 9), // "doPeerOld"
QT_MOC_LITERAL(10, 98, 12), // "doDestroyOld"
QT_MOC_LITERAL(11, 111, 11), // "doPeerOldOK"
QT_MOC_LITERAL(12, 123, 13), // "doDeployOldOK"
QT_MOC_LITERAL(13, 137, 13), // "doMethodOldOK"
QT_MOC_LITERAL(14, 151, 14), // "doDestroyOldOK"
QT_MOC_LITERAL(15, 166, 10), // "doBlockNew"
QT_MOC_LITERAL(16, 177, 11), // "doDeployNew"
QT_MOC_LITERAL(17, 189, 11), // "doMethodNew"
QT_MOC_LITERAL(18, 201, 9), // "doPeerNew"
QT_MOC_LITERAL(19, 211, 12), // "doDestroyNew"
QT_MOC_LITERAL(20, 224, 11), // "doPeerNewOK"
QT_MOC_LITERAL(21, 236, 13), // "doDeployNewOK"
QT_MOC_LITERAL(22, 250, 13), // "doMethodNewOK"
QT_MOC_LITERAL(23, 264, 14), // "doDestroyNewOK"
QT_MOC_LITERAL(24, 279, 11), // "doSaveBlock"
QT_MOC_LITERAL(25, 291, 16), // "doBlockOldFinish"
QT_MOC_LITERAL(26, 308, 17), // "doBroadcastAppOld"
QT_MOC_LITERAL(27, 326, 17), // "doBroadcastAppNew"
QT_MOC_LITERAL(28, 344, 12), // "doUpdPeerNew"
QT_MOC_LITERAL(29, 357, 26), // "doBroadcastBlockChainLevel"
QT_MOC_LITERAL(30, 384, 2), // "id"
QT_MOC_LITERAL(31, 387, 5), // "level"
QT_MOC_LITERAL(32, 393, 23), // "doRequireBlockChainData"
QT_MOC_LITERAL(33, 417, 11), // "nodeAddress"
QT_MOC_LITERAL(34, 429, 5), // "start"
QT_MOC_LITERAL(35, 435, 3), // "end"
QT_MOC_LITERAL(36, 439, 20), // "doSendBlockChainData"
QT_MOC_LITERAL(37, 460, 4), // "data"
QT_MOC_LITERAL(38, 465, 13), // "doSetBossList"
QT_MOC_LITERAL(39, 479, 15), // "doCustomRequire"
QT_MOC_LITERAL(40, 495, 10), // "contractID"
QT_MOC_LITERAL(41, 506, 4), // "addr"
QT_MOC_LITERAL(42, 511, 3), // "cmd"
QT_MOC_LITERAL(43, 515, 17), // "doCustomBroadcast"
QT_MOC_LITERAL(44, 533, 13), // "doBossMissing"
QT_MOC_LITERAL(45, 547, 6), // "onInit"
QT_MOC_LITERAL(46, 554, 12), // "onInitFinish"
QT_MOC_LITERAL(47, 567, 7), // "onStart"
QT_MOC_LITERAL(48, 575, 13), // "onStartFinish"
QT_MOC_LITERAL(49, 589, 9), // "onTimeout"
QT_MOC_LITERAL(50, 599, 10), // "onBlockOld"
QT_MOC_LITERAL(51, 610, 11), // "onDeployOld"
QT_MOC_LITERAL(52, 622, 11), // "onMethodOld"
QT_MOC_LITERAL(53, 634, 9), // "onPeerOld"
QT_MOC_LITERAL(54, 644, 12), // "onDestroyOld"
QT_MOC_LITERAL(55, 657, 11), // "onPeerOldOK"
QT_MOC_LITERAL(56, 669, 13), // "onDeployOldOK"
QT_MOC_LITERAL(57, 683, 13), // "onMethodOldOK"
QT_MOC_LITERAL(58, 697, 14), // "onDestroyOldOK"
QT_MOC_LITERAL(59, 712, 10), // "onBlockNew"
QT_MOC_LITERAL(60, 723, 11), // "onDeployNew"
QT_MOC_LITERAL(61, 735, 11), // "onMethodNew"
QT_MOC_LITERAL(62, 747, 9), // "onPeerNew"
QT_MOC_LITERAL(63, 757, 12), // "onDestroyNew"
QT_MOC_LITERAL(64, 770, 11), // "onPeerNewOK"
QT_MOC_LITERAL(65, 782, 13), // "onDeployNewOK"
QT_MOC_LITERAL(66, 796, 13), // "onMethodNewOK"
QT_MOC_LITERAL(67, 810, 14), // "onDestroyNewOK"
QT_MOC_LITERAL(68, 825, 11), // "onSaveBlock"
QT_MOC_LITERAL(69, 837, 16), // "onBlockOldFinish"
QT_MOC_LITERAL(70, 854, 10), // "onUdpdPeer"
QT_MOC_LITERAL(71, 865, 26), // "onBroadcastBlockChainLevel"
QT_MOC_LITERAL(72, 892, 23), // "onRequireBlockChainData"
QT_MOC_LITERAL(73, 916, 20), // "onSendBlockChainData"
QT_MOC_LITERAL(74, 937, 15), // "onCustomRequire"
QT_MOC_LITERAL(75, 953, 13) // "onBossMissing"

    },
    "onnObject\0doInit\0\0doInitFinish\0doStart\0"
    "doStartFinish\0doBlockOld\0doDeployOld\0"
    "doMethodOld\0doPeerOld\0doDestroyOld\0"
    "doPeerOldOK\0doDeployOldOK\0doMethodOldOK\0"
    "doDestroyOldOK\0doBlockNew\0doDeployNew\0"
    "doMethodNew\0doPeerNew\0doDestroyNew\0"
    "doPeerNewOK\0doDeployNewOK\0doMethodNewOK\0"
    "doDestroyNewOK\0doSaveBlock\0doBlockOldFinish\0"
    "doBroadcastAppOld\0doBroadcastAppNew\0"
    "doUpdPeerNew\0doBroadcastBlockChainLevel\0"
    "id\0level\0doRequireBlockChainData\0"
    "nodeAddress\0start\0end\0doSendBlockChainData\0"
    "data\0doSetBossList\0doCustomRequire\0"
    "contractID\0addr\0cmd\0doCustomBroadcast\0"
    "doBossMissing\0onInit\0onInitFinish\0"
    "onStart\0onStartFinish\0onTimeout\0"
    "onBlockOld\0onDeployOld\0onMethodOld\0"
    "onPeerOld\0onDestroyOld\0onPeerOldOK\0"
    "onDeployOldOK\0onMethodOldOK\0onDestroyOldOK\0"
    "onBlockNew\0onDeployNew\0onMethodNew\0"
    "onPeerNew\0onDestroyNew\0onPeerNewOK\0"
    "onDeployNewOK\0onMethodNewOK\0onDestroyNewOK\0"
    "onSaveBlock\0onBlockOldFinish\0onUdpdPeer\0"
    "onBroadcastBlockChainLevel\0"
    "onRequireBlockChainData\0onSendBlockChainData\0"
    "onCustomRequire\0onBossMissing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_onnObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      65,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      34,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  339,    2, 0x06 /* Public */,
       3,    0,  340,    2, 0x06 /* Public */,
       4,    0,  341,    2, 0x06 /* Public */,
       5,    0,  342,    2, 0x06 /* Public */,
       6,    1,  343,    2, 0x06 /* Public */,
       7,    1,  346,    2, 0x06 /* Public */,
       8,    1,  349,    2, 0x06 /* Public */,
       9,    1,  352,    2, 0x06 /* Public */,
      10,    1,  355,    2, 0x06 /* Public */,
      11,    1,  358,    2, 0x06 /* Public */,
      12,    2,  361,    2, 0x06 /* Public */,
      13,    2,  366,    2, 0x06 /* Public */,
      14,    1,  371,    2, 0x06 /* Public */,
      15,    1,  374,    2, 0x06 /* Public */,
      16,    1,  377,    2, 0x06 /* Public */,
      17,    1,  380,    2, 0x06 /* Public */,
      18,    1,  383,    2, 0x06 /* Public */,
      19,    1,  386,    2, 0x06 /* Public */,
      20,    1,  389,    2, 0x06 /* Public */,
      21,    2,  392,    2, 0x06 /* Public */,
      22,    2,  397,    2, 0x06 /* Public */,
      23,    1,  402,    2, 0x06 /* Public */,
      24,    2,  405,    2, 0x06 /* Public */,
      25,    0,  410,    2, 0x06 /* Public */,
      26,    1,  411,    2, 0x06 /* Public */,
      27,    1,  414,    2, 0x06 /* Public */,
      28,    2,  417,    2, 0x06 /* Public */,
      29,    2,  422,    2, 0x06 /* Public */,
      32,    4,  427,    2, 0x06 /* Public */,
      36,    3,  436,    2, 0x06 /* Public */,
      38,    1,  443,    2, 0x06 /* Public */,
      39,    4,  446,    2, 0x06 /* Public */,
      43,    3,  455,    2, 0x06 /* Public */,
      44,    1,  462,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      45,    0,  465,    2, 0x0a /* Public */,
      46,    0,  466,    2, 0x0a /* Public */,
      47,    0,  467,    2, 0x0a /* Public */,
      48,    0,  468,    2, 0x0a /* Public */,
      49,    0,  469,    2, 0x0a /* Public */,
      50,    1,  470,    2, 0x0a /* Public */,
      51,    1,  473,    2, 0x0a /* Public */,
      52,    1,  476,    2, 0x0a /* Public */,
      53,    1,  479,    2, 0x0a /* Public */,
      54,    1,  482,    2, 0x0a /* Public */,
      55,    1,  485,    2, 0x0a /* Public */,
      56,    2,  488,    2, 0x0a /* Public */,
      57,    2,  493,    2, 0x0a /* Public */,
      58,    1,  498,    2, 0x0a /* Public */,
      59,    1,  501,    2, 0x0a /* Public */,
      60,    1,  504,    2, 0x0a /* Public */,
      61,    1,  507,    2, 0x0a /* Public */,
      62,    1,  510,    2, 0x0a /* Public */,
      63,    1,  513,    2, 0x0a /* Public */,
      64,    1,  516,    2, 0x0a /* Public */,
      65,    2,  519,    2, 0x0a /* Public */,
      66,    2,  524,    2, 0x0a /* Public */,
      67,    1,  529,    2, 0x0a /* Public */,
      68,    2,  532,    2, 0x0a /* Public */,
      69,    0,  537,    2, 0x0a /* Public */,
      70,    3,  538,    2, 0x0a /* Public */,
      71,    3,  545,    2, 0x0a /* Public */,
      72,    4,  552,    2, 0x0a /* Public */,
      73,    3,  561,    2, 0x0a /* Public */,
      74,    4,  568,    2, 0x0a /* Public */,
      75,    1,  577,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   30,   31,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   30,   33,   34,   35,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   30,   33,   37,
    QMetaType::Void, QMetaType::QByteArrayList,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::QString, QMetaType::QString,   40,   41,   42,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   40,   42,   37,
    QMetaType::Void, QMetaType::QByteArrayList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QByteArray,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   40,   41,   42,   37,
    QMetaType::Void, QMetaType::QByteArrayList,    2,

       0        // eod
};

void onnObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        onnObject *_t = static_cast<onnObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doInit(); break;
        case 1: _t->doInitFinish(); break;
        case 2: _t->doStart(); break;
        case 3: _t->doStartFinish(); break;
        case 4: _t->doBlockOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->doDeployOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->doMethodOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->doPeerOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->doDestroyOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 9: _t->doPeerOldOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->doDeployOldOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 11: _t->doMethodOldOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 12: _t->doDestroyOldOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 13: _t->doBlockNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->doDeployNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: _t->doMethodNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 16: _t->doPeerNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 17: _t->doDestroyNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 18: _t->doPeerNewOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 19: _t->doDeployNewOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 20: _t->doMethodNewOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 21: _t->doDestroyNewOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 22: _t->doSaveBlock((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 23: _t->doBlockOldFinish(); break;
        case 24: _t->doBroadcastAppOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 25: _t->doBroadcastAppNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 26: _t->doUpdPeerNew((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 27: _t->doBroadcastBlockChainLevel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 28: _t->doRequireBlockChainData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 29: _t->doSendBlockChainData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 30: _t->doSetBossList((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        case 31: _t->doCustomRequire((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 32: _t->doCustomBroadcast((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 33: _t->doBossMissing((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        case 34: _t->onInit(); break;
        case 35: _t->onInitFinish(); break;
        case 36: _t->onStart(); break;
        case 37: _t->onStartFinish(); break;
        case 38: _t->onTimeout(); break;
        case 39: _t->onBlockOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 40: _t->onDeployOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 41: _t->onMethodOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 42: _t->onPeerOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 43: _t->onDestroyOld((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 44: _t->onPeerOldOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 45: _t->onDeployOldOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 46: _t->onMethodOldOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 47: _t->onDestroyOldOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 48: _t->onBlockNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 49: _t->onDeployNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 50: _t->onMethodNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 51: _t->onPeerNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 52: _t->onDestroyNew((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 53: _t->onPeerNewOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 54: _t->onDeployNewOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 55: _t->onMethodNewOK((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 56: _t->onDestroyNewOK((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 57: _t->onSaveBlock((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 58: _t->onBlockOldFinish(); break;
        case 59: _t->onUdpdPeer((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 60: _t->onBroadcastBlockChainLevel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 61: _t->onRequireBlockChainData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 62: _t->onSendBlockChainData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 63: _t->onCustomRequire((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 64: _t->onBossMissing((*reinterpret_cast< QByteArrayList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (onnObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doInit)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (onnObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doInitFinish)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (onnObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doStart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (onnObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doStartFinish)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBlockOld)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDeployOld)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doMethodOld)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doPeerOld)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDestroyOld)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doPeerOldOK)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDeployOldOK)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doMethodOldOK)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDestroyOldOK)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBlockNew)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDeployNew)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doMethodNew)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doPeerNew)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDestroyNew)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doPeerNewOK)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDeployNewOK)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doMethodNewOK)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doDestroyNewOK)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doSaveBlock)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (onnObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBlockOldFinish)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBroadcastAppOld)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBroadcastAppNew)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QStringList , QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doUpdPeerNew)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBroadcastBlockChainLevel)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doRequireBlockChainData)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doSendBlockChainData)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArrayList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doSetBossList)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QString , QByteArray , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doCustomRequire)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doCustomBroadcast)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (onnObject::*)(QByteArrayList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&onnObject::doBossMissing)) {
                *result = 33;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject onnObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_onnObject.data,
      qt_meta_data_onnObject,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *onnObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *onnObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_onnObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int onnObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 65)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 65;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 65)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 65;
    }
    return _id;
}

// SIGNAL 0
void onnObject::doInit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void onnObject::doInitFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void onnObject::doStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void onnObject::doStartFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void onnObject::doBlockOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void onnObject::doDeployOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void onnObject::doMethodOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void onnObject::doPeerOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void onnObject::doDestroyOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void onnObject::doPeerOldOK(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void onnObject::doDeployOldOK(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void onnObject::doMethodOldOK(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void onnObject::doDestroyOldOK(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void onnObject::doBlockNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void onnObject::doDeployNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void onnObject::doMethodNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void onnObject::doPeerNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void onnObject::doDestroyNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void onnObject::doPeerNewOK(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void onnObject::doDeployNewOK(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void onnObject::doMethodNewOK(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void onnObject::doDestroyNewOK(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void onnObject::doSaveBlock(QByteArray _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void onnObject::doBlockOldFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void onnObject::doBroadcastAppOld(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void onnObject::doBroadcastAppNew(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void onnObject::doUpdPeerNew(QStringList _t1, QStringList _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void onnObject::doBroadcastBlockChainLevel(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void onnObject::doRequireBlockChainData(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void onnObject::doSendBlockChainData(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void onnObject::doSetBossList(QByteArrayList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void onnObject::doCustomRequire(QString _t1, QByteArray _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void onnObject::doCustomBroadcast(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void onnObject::doBossMissing(QByteArrayList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
