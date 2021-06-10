TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -std=c++2a
SOURCES += \
        machine.cpp \
        main.cpp \
        member.cpp \
        membermanager.cpp

HEADERS += \
    machine.h \
    member.h \
    membermanager.h
