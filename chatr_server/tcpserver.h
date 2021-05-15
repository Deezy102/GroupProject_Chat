#pragma once
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "database.h"
#include <QCoreApplication>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>


class tcpServer : public QObject
{
    Q_OBJECT
public:
    explicit tcpServer(QObject *parent = nullptr);
    ~tcpServer();

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotDisconect();
    void slotServerWriteMessage(string message);

private:
    QTcpServer * serv;
    QTcpSocket * sock;
    bool server_status;
    int user_counts;
    std::string msg;
    QMap<int, QTcpSocket*> mp;
    const QString ipAddress = "127.0.0.1";
<<<<<<< HEAD
=======

signals:
    bool check(string logpass);


>>>>>>> a17c4a4 (old ver)
};

#endif // TCPSERVER_H
