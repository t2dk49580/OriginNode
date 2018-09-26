#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T10:57:17
#
#-------------------------------------------------

QT       -= core gui

TARGET = openssl
TEMPLATE = lib

DEFINES += OPENSSL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        c.cpp \
    c.cpp \
    auxiliar/auxiliar.c \
    auxiliar/subsidiar.c \
    src/asn1.c \
    src/bio.c \
    src/callback.c \
    src/cipher.c \
    src/cms.c \
    src/compat.c \
    src/crl.c \
    src/csr.c \
    src/ocsp.c \
    src/dh.c \
    src/digest.c \
    src/dsa.c \
    src/ec.c \
    src/engine.c \
    src/hmac.c \
    src/lbn.c \
    src/lhash.c \
    src/misc.c \
    src/openssl.c \
    src/ots.c \
    src/pkcs12.c \
    src/pkcs7.c \
    src/pkey.c \
    src/rsa.c \#src/sm2.c \
    src/srp.c \
    src/ssl.c \
    src/th-lock.c \
    src/util.c \
    src/x509.c \
    src/xalgor.c \
    src/xattrs.c \
    src/xexts.c \
    src/xname.c \
    src/xstore.c \
    c.cpp \
    lapi.c \
    lauxlib.c \
    lbaselib.c \
    lbitlib.c \
    lcode.c \
    lcorolib.c \
    lctype.c \
    ldblib.c \
    ldebug.c \
    ldo.c \
    ldump.c \
    lfunc.c \
    lgc.c \
    linit.c \
    liolib.c \
    llex.c \
    lmathlib.c \
    lmem.c \
    loadlib.c \
    lobject.c \
    lopcodes.c \
    loslib.c \
    lparser.c \
    lstate.c \
    lstring.c \
    lstrlib.c \
    ltable.c \
    ltablib.c \
    ltm.c \
    lua.c \
    luac.c \
    lundump.c \
    lutf8lib.c \
    lvm.c \
    lzio.c

HEADERS += \
        h.h \
        openssl_global.h \ 
    auxiliar/auxiliar.h \
    auxiliar/subsidiar.h \
    src/openssl.h \
    src/private.h \
    src/sk.h \
    src/ssl_options.h \
    h.h \
    openssl_global.h \
    h.h \
    lapi.h \
    lauxlib.h \
    lcode.h \
    lctype.h \
    ldebug.h \
    ldo.h \
    lfunc.h \
    lgc.h \
    llex.h \
    llimits.h \
    lmem.h \
    lobject.h \
    lopcodes.h \
    lparser.h \
    lprefix.h \
    lstate.h \
    lstring.h \
    ltable.h \
    ltm.h \
    lua.h \
    lua.hpp \
    luaconf.h \
    lualib.h \
    lundump.h \
    lvm.h \
    lzio.h \
    openssl_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SUBDIRS += \
    openssl.pro \
    openssl.pro

DISTFILES += \
    auxiliar/readme.md \
    src/config.ld \
    src/oids.txt \
    openssl.pro.user \
    Makefile

INCLUDEPATH += ../../deps/luaopenssl/include
LIBS += -L../../deps/lib -lssl11 -lcrypto11 -ldl
