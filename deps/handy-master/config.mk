CC=cc
CXX=g++
PLATFORM=OS_LINUX
PLATFORM_LDFLAGS=-pthread -L/home/sai/code/OriginNode/deps/handy-master
PLATFORM_LIBS=
PLATFORM_CCFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/home/sai/code/OriginNode/deps/handy-master
PLATFORM_CXXFLAGS=  -pthread -DOS_LINUX -DLITTLE_ENDIAN=1 -std=c++11 -I/home/sai/code/OriginNode/deps/handy-master
PLATFORM_SHARED_CFLAGS=-fPIC
PLATFORM_SHARED_EXT=so
PLATFORM_SHARED_LDFLAGS=-shared -Wl,-soname -Wl,
PLATFORM_SHARED_VERSIONED=true
