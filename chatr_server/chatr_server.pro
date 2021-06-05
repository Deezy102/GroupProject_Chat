QT -= gui

QT += network
QT += sql
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += D:/qt/Tools/OpenSSL/Win_x64/include/openssl/
LIBS += D:/qt/Tools/OpenSSL/Win_x64/lib/libcrypto.lib



SOURCES += \
        database.cpp \
        main.cpp \
        tcpserver.cpp
include(D:/Chat_project/123/test/test/Qt-Secret/src/Qt-Secret.pri)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    database.h \
    tcpserver.h
