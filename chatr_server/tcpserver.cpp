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
    if (server_status)
    {
        const auto keys = mp.keys();

        foreach(int i, keys)
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

        qDebug() << QString::fromUtf8("У нас новое соединение (сокет: %1). Количество пользователей:").arg(id) << user_counts;

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

        if (keyWord == "auth")
            transfer = authorization(msg + "&" + std::to_string(clientsock->socketDescriptor()));

        else if (keyWord== "reg")
            transfer = registration(msg);

        else if (keyWord == "msg")
            transfer = message(msg);

        else if (keyWord == "chatcrt")
            transfer = chatCreation(msg);

        else if (keyWord == "chatUserAdd")
            transfer = chatUserAdd(msg);

        else if (keyWord == "chatUserDel")
            transfer = chatUserDel(msg);

        else if  (keyWord == "chatld")
            slotLoadChatRoom(msg);

        else if (keyWord == "list")
            slotServerSendChatlist(msg);


        if (transfer.contains("msg&"))
            slotServerWriteMessage(transfer.toStdString());
        else
            clientsock->write(transfer);
    }
}

void tcpServer::slotServerWriteMessage(string chatName)
{
    chatName.erase(0,chatName.find("&") + 1);

    string chatNameCopy = chatName;

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

        int id = loginToSocket(buf);

        if (id != 0)
            mp[id]->write(read_from_file(chatNameCopy, 1));
    }
}

void tcpServer::slotDisconect()
{
    QTcpSocket *clientsock = (QTcpSocket*)sender();

    const auto keys = mp.keys();

    foreach(int i, keys)
        if (mp[i] == clientsock)
        {
            mp.remove(i);
            BDSocketClear(i);
            qDebug() << "client disconected: " << i;
        }

    user_counts--;
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
                mp[id]->write(read_from_file(chatName, 1));
        }
        else//просмотр старых сообщений
        {
            for (int i = 50 * (multiplier - 1) + 1; i < 50 * multiplier + 1; i++)
                //добавить проверку на пустую строку либо здесь либо в чтении из файла
                mp[id]->write(read_from_file(chatName, 1));
        }
    }

}
