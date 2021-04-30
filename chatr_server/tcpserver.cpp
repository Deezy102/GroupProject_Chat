#include "tcpserver.h"



tcpServer::tcpServer(QObject *parent) : QObject(parent)
{
    serv = new QTcpServer(this);
    connect(serv, &QTcpServer::newConnection,this, &tcpServer::slotNewConnection);

    if (serv->listen(QHostAddress(ipAddress), 12345))
    {
        server_status = true;
        user_counts = 0;
        qDebug() << "server started";
    }
    else
        qDebug() << "server not started";
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
        qDebug() << QString::fromUtf8("У нас новое соединение! Количество пользователей ") << user_counts;
        QTcpSocket* clientSock=serv->nextPendingConnection();
        int id = clientSock->socketDescriptor();
        mp[id] = clientSock;
        mp[id]->write("u connected to the server");
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
        clientsock->write(parsing(msg));
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


