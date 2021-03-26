#include "tcpserver.h"
#include <QCoreApplication>
#include <QDebug>

tcpServer::tcpServer(QObject *parent) : QObject(parent)
{
    serv = new QTcpServer(this);
    connect(serv, &QTcpServer::newConnection,this, &tcpServer::slotNewConnection);

    if (serv->listen(QHostAddress("192.168.1.5"), 12345))
    {
        server_status = true;
        user_counts = 0;
        qDebug() << "started";
    }
    else
        qDebug() << "not started";
}

tcpServer::~tcpServer()
{
    if (server_status)
    {
        foreach(int i, mp.keys())
        {
            mp[i]->close();
            mp.remove(i);
        }
        serv->close();
        server_status = false;
    }
}

void tcpServer::slotNewConnection()
{
    if (server_status)
    {
        user_counts++;
        qDebug() << QString::fromUtf8("У нас новое соединение!\nКоличество пользователей ") << user_counts;
        QTcpSocket* clientSock=serv->nextPendingConnection();
        int id = clientSock->socketDescriptor();
        mp[id] = clientSock;
        mp[id]->write("vlad xyi");
        connect(mp[id], &QTcpSocket::readyRead, this, &tcpServer::slotServerRead);
        connect(mp[id], &QTcpSocket::disconnected, this, &tcpServer::slotDisconect);
    }
}

void tcpServer::slotServerRead()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    while(clientsock->bytesAvailable() > 0)
    {
        QByteArray arr = clientsock->readAll();
        msg = arr.toStdString();
        qDebug() << QString::fromStdString(msg);
    }
}

void tcpServer::slotDisconect()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();
    int id = (int)clientsock->socketDescriptor();
    clientsock->close();
    mp.remove(id);
    user_counts--;
    qDebug() << "client disconected";
}
