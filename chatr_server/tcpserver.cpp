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

    oldSocketsClear();
}

tcpServer::~tcpServer()
{
//    qDebug() << "destruct";
    if (server_status)
    {
        foreach(int i, mp.keys())
        {
            mp[i]->close();
            mp.remove(i);
            BDSocketClear(i);
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
        QTcpSocket* clientSock=serv->nextPendingConnection();
        int id = clientSock->socketDescriptor();
        mp[id] = clientSock;
        mp[id]->write("u connected to the server");

        qDebug() << QString::fromUtf8("У нас новое соединение! Количество пользователей ") << user_counts << id;

        connect(mp[id], &QTcpSocket::readyRead, this, &tcpServer::slotServerRead);
        connect(mp[id], &QTcpSocket::disconnected, this, &tcpServer::slotDisconect);
    }
}

void tcpServer::slotServerRead()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    while(clientsock->bytesAvailable() > 0)
    {
        QByteArray transfer = clientsock->readAll();
        msg = transfer.toStdString();

        string keyWord = msg.substr(0,msg.find("&"));
        msg.erase(0,keyWord.size() + 1);

        //QByteArray receive;

        if (keyWord == "auth")
        {
            //qDebug() << "auth" << clientsock->socketDescriptor();
            transfer = authorization(msg + "&" + std::to_string(clientsock->socketDescriptor()));
        }
        if (keyWord== "reg")
        {
            transfer = registration(msg);
        }
        if (keyWord == "msg")
        {
            transfer = message(msg);
        }
        if (keyWord == "chatcrt")
        {
            transfer = chatCreation(msg);
        }
        if (keyWord == "chatUserAdd")
        {
            transfer = chatUserAdd(msg);
        }
        if (transfer.contains("msg&"))
        {
            //qDebug() << "mes&";
            slotServerWriteMessage(transfer.toStdString());
        }
        else
            clientsock->write(transfer);
    }
}

void tcpServer::slotServerWriteMessage(string chatName)
{
    //QTcpSocket *clientsock = (QTcpSocket*)sender();

    chatName.erase(0,chatName.find("&") + 1);

    string chatNameCopy = chatName;

    qDebug() << "chatName: " << QString::fromStdString(chatName);

    while (!chatName.empty())
    {
        string buf = "";
        if (chatName.find("_") != string::npos)
        {
            buf = chatName.substr(0, chatName.find("_"));
            chatName.erase(0, chatName.find("_") + 1);
        }
        else
        {
            buf = chatName;
            chatName.erase(0, chatName.length());
        }
        //qDebug() << "serverwrite: " << QString::fromStdString(buf);

        int id = loginToSocket(buf);
        if (id != 0)
            mp[id]->write(QByteArray::fromStdString(read_from_file(chatNameCopy, 1)));

    }

    //clientsock->write(QByteArray::fromStdString(read_from_file(chatName)));

}

void tcpServer::slotDisconect()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    foreach(int i, mp.keys())
    {
        if (mp[i] == clientsock)
            {
            mp.remove(i);
            BDSocketClear(i);
            qDebug() << "client disconected: " << i;
            }
    }

    user_counts--;

}
