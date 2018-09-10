QT -= gui
QT += network websockets concurrent

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    onnObject.cpp \
    ssl/ecdsa.cpp \
    ssl/ecmult.cpp \
    ssl/field.cpp \
    ssl/group.cpp \
    ssl/num_openssl.cpp \
    ssl/secp256k1.cpp \
    onnSystem.cpp \
    onnDatabase.cpp \
    onnContract.cpp \
    onnHttpd.cpp \
    onnWebsocketd.cpp \
    onnUdpd.cpp \
    onnChecker.cpp \
    ovm/lapi.c \
    ovm/lauxlib.c \
    ovm/lbaselib.c \
    ovm/lbitlib.c \
    ovm/lcode.c \
    ovm/lcorolib.c \
    ovm/lctype.c \
    ovm/ldblib.c \
    ovm/ldebug.c \
    ovm/ldo.c \
    ovm/ldump.c \
    ovm/lfunc.c \
    ovm/lgc.c \
    ovm/linit.c \
    ovm/liolib.c \
    ovm/llex.c \
    ovm/lmathlib.c \
    ovm/lmem.c \
    ovm/loadlib.c \
    ovm/lobject.c \
    ovm/lopcodes.c \
    ovm/loslib.c \
    ovm/lparser.c \
    ovm/lstate.c \
    ovm/lstring.c \
    ovm/lstrlib.c \
    ovm/ltable.c \
    ovm/ltablib.c \
    ovm/ltm.c \
    ovm/lua.c \
    ovm/luac.c \
    ovm/lundump.c \
    ovm/lutf8lib.c \
    ovm/lvm.c \
    ovm/lzio.c \
    uws/Epoll.cpp \
    uws/Extensions.cpp \
    uws/Group.cpp \
    uws/HTTPSocket.cpp \
    uws/Hub.cpp \
    uws/Networking.cpp \
    uws/Node.cpp \
    uws/Socket.cpp \
    uws/WebSocket.cpp

include("./src/Crypto/EmccSDK/nemcc/nemcc.pri")
include("./NetSync/netsync.pri")

#LIBS += -luWS -lz -lcrypto -lssl -llua5.3 -lleveldb -lhandy

INCLUDEPATH += ./deps/openssl10/include ./deps/include
LIBS += -lssl10 -lcrypto10 -lz -lleveldb -lhandy -ldl

HEADERS += \
    onnDefine.h \
    onnObject.h \
    ssl/ecdsa.h \
    ssl/ecmult.h \
    ssl/field.h \
    ssl/group.h \
    ssl/num_openssl.h \
    ssl/secp256k1.h \
    onnSystem.h \
    onnDatabase.h \
    onnContract.h \
    onnHttpd.h \
    onnWebsocketd.h \
    onnUdpd.h \
    onnChecker.h \
    ovm/lapi.h \
    ovm/lauxlib.h \
    ovm/lcode.h \
    ovm/lctype.h \
    ovm/ldebug.h \
    ovm/ldo.h \
    ovm/lfunc.h \
    ovm/lgc.h \
    ovm/llex.h \
    ovm/llimits.h \
    ovm/lmem.h \
    ovm/lobject.h \
    ovm/lopcodes.h \
    ovm/lparser.h \
    ovm/lprefix.h \
    ovm/lstate.h \
    ovm/lstring.h \
    ovm/ltable.h \
    ovm/ltm.h \
    ovm/lua.h \
    ovm/lua.hpp \
    ovm/luaconf.h \
    ovm/lualib.h \
    ovm/lundump.h \
    ovm/lvm.h \
    ovm/lzio.h \
    uws/Asio.h \
    uws/Backend.h \
    uws/Epoll.h \
    uws/Extensions.h \
    uws/Group.h \
    uws/HTTPSocket.h \
    uws/Hub.h \
    uws/Libuv.h \
    uws/Networking.h \
    uws/Node.h \
    uws/Socket.h \
    uws/uWS.h \
    uws/WebSocket.h \
    uws/WebSocketProtocol.h
