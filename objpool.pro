TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

HEADERS += \
    includes/opool.h \
    includes/opoolexceptions.h \
    includes/poolable.h \
    includes/sopool.h

SOURCES += \
    source/main.cpp \
    tests/test.cpp

DISTFILES += \
    .gitignore \
    LICENSE.md \
    README.md

