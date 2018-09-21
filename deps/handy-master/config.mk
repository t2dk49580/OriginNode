CC=cc
CXX=g++
PLATFORM=OS_LINUX
PLATFORM_LDFLAGS=-pthread -L/home/sai/code/git/OriginNode/deps/handy-master
PLATFORM_LIBS= -lssl -lcrypto
PLATFORM_CCFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/home/sai/code/git/OriginNode/deps/handy-master
PLATFORM_CXXFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/home/sai/code/git/OriginNode/deps/handy-master
PLATFORM_SHARED_CFLAGS=-fPIC
PLATFORM_SHARED_EXT=so
PLATFORM_SHARED_LDFLAGS=-shared -Wl,-soname -Wl,
PLATFORM_SHARED_VERSIONED=true
HANDY_SOURCES=ssl/ssl-conn.cc
EXAMPLE_SOURCES=ssl/ssl-cli.cc ssl/ssl-svr.cc ssl/https-svr.cc
