TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
CONFIG += network
CONFIG += c++11

SOURCES += main.cpp

HEADERS += \
    opool.h \
    poolable.h \
    opoolexceptions.h \
    sopool.h
