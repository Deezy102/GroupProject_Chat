#include "tcpserver.h"
#include <QCoreApplication>
#include "functions.h"

tcpServer::tcpServer(QObject *parent) : QObject(parent)
{
    serv = new QTcpServer(this);
    connect(serv, &QTcpServer::newConnection,this, &tcpServer::slotNewConnection);

    if (serv->listen(QHostAddress("127.0.0.1"), 12345))
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
        qDebug() << QString::fromUtf8("У нас новое соединение! Количество пользователей ") << user_counts;
        QTcpSocket* clientSock=serv->nextPendingConnection();
        int id = clientSock->socketDescriptor();
        mp[id] = clientSock;
        mp[id]->write("Hello");
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

QByteArray parsing(string msg)
{
    string buf = msg.substr(0,msg.find("&"));
    msg.erase(0,buf.size() + 1);
    if (buf == "auth")
    {
        if (check(msg))
            return "successful login";
        else
            return "invalid login or password";
    }
    if (buf == "reg")
    {
        if (registration(msg))
            return "successful reg";
        else
            return "choose antoher login";
    }
}
