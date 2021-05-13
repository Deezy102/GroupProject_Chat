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
    qDebug() << "destruct";
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
        qDebug() << "slotnewcon" << id;
        mp[id] = clientSock;
        mp[id]->write("u connected to the server");
        connect(mp[id], &QTcpSocket::readyRead, this, &tcpServer::slotServerRead);
        connect(mp[id], &QTcpSocket::disconnected, this, &tcpServer::slotDisconect);
        //connect(mp[id], &QTcpSocket::disconnected, this, &tcpServer::deleteLater);
       // connect(mp[id],SIGNAL(disconnected()),mp[id] , SLOT(deleteLater()));
    }
}

void tcpServer::slotServerRead()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    while(clientsock->bytesAvailable() > 0)
    {
        QByteArray arr = clientsock->readAll();
        msg = arr.toStdString();

        string buf = msg.substr(0,msg.find("&"));
        msg.erase(0,buf.size() + 1);

        QByteArray receive;

        if (buf == "auth")
        {
            qDebug() << "auth" << clientsock->socketDescriptor();
            receive = authorization(msg + "&" + std::to_string(clientsock->socketDescriptor()));
        }
        if (buf == "reg")
            receive = registration(msg);
        if (buf == "msg")
            receive = message(msg);


        if (receive.contains("msg&"))
        {
            slotServerWriteMessage(receive.toStdString());
        }
        else
            clientsock->write(receive);
    }
}

void tcpServer::slotServerWriteMessage(string message)
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();
    message.erase(0,message.find("&") + 1);

    clientsock->write(QByteArray::fromStdString(read_from_file(message)));

}

void tcpServer::slotDisconect()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    //int id = -1;

    foreach(int i, mp.keys())
    {
        if (mp[i] == clientsock)
            {
            mp.remove(i);
            discon(i);
            qDebug() << "client disconected: " << i;
            }
    }

    user_counts--;

}
