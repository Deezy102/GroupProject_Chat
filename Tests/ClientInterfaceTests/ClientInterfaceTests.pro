QT += testlib
QT += core
QT -= gui
QT += quick network

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testfuncs.cpp \
    ../../ClientInterface/Funcs.cpp

HEADERS += \
    ../../ClientInterface/Funcs.h
