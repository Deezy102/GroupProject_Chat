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
        QByteArray recieve = clientsock->readAll();
        msg = recieve.toStdString();

        string keyWord = msg.substr(0,msg.find("&"));
        msg.erase(0,keyWord.size() + 1);

        //QByteArray receive;

        if (keyWord == "auth")
        {
            //qDebug() << "auth" << clientsock->socketDescriptor();
            recieve = authorization(msg + "&" + std::to_string(clientsock->socketDescriptor()));
        }
        if (keyWord== "reg")
        {
            recieve = registration(msg);
        }
        if (keyWord == "msg")
        {
            recieve = message(msg);
        }
        if (keyWord == "chatcrt")
        {
            recieve = chatCreation(msg);
        }
        if  (keyWord == "chatld")
        {
            slotLoadChatRoom(msg);
        }
        if (keyWord == "list")
        {
            slotServerSendChatlist(msg);
        }
        if (recieve.contains("msg&"))
        {
            //qDebug() << "mes&";
            slotServerWriteMessage(recieve.toStdString());
        }

        else
            clientsock->write(recieve);
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
            mp[id]->write(QByteArray::fromStdString(read_from_file(chatNameCopy, 0)));//поменял второй аргумент из-за изменения функции

    }

    //clientsock->write(QByteArray::fromStdString(read_from_file(chatName)));

}
void tcpServer::slotServerSendChatlist(string login)
{
    //вектор стрингов хранит список чатов, в которых состоит пользователь
    vector<string> list = getChatlist(login);

    int id = loginToSocket(login); //получаем сокет по логину

    if (id != 0)
        for (int i = 0; i < list.size(); i++)//посылаем на клиент по одному названию чата
            mp[id]->write(QByteArray::fromStdString(std::to_string(i+1)+ ". " + list[i]));

}

void tcpServer::slotLoadChatRoom(string servmsg)
{
    //парсим полученное сервером сообщение
    string login = servmsg.substr(0,servmsg.find("&"));
    string chatName = servmsg.substr(servmsg.find("&") + 1, servmsg.rfind("&") - servmsg.find("&") - 1);
    int multiplier = std::stoi(servmsg.substr(servmsg.rfind("&") + 1, servmsg.length()));

    int id = loginToSocket(login);//получаем сокет по логину
    if(id != 0)
    {
        //посылаю на клиент по одному сообщению из диапазона, зависящем от множителя, который хранится на клиенте
        //и передается в служебном сообщении
        if (multiplier == 1)//первое открытие переписки
        {
            for (int i = 0; i < 51; i++)
                //добавить проверку на пустую строку либо здесь либо в чтении из файла
                mp[id]->write(QByteArray::fromStdString(read_from_file(chatName, i)));
        }
        else//просмотр старых сообщений
        {
            for (int i = 50 * (multiplier - 1) + 1; i < 50 * multiplier + 1; i++)
                //добавить проверку на пустую строку либо здесь либо в чтении из файла
                mp[id]->write(QByteArray::fromStdString(read_from_file(chatName, i)));
        }
    }

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
