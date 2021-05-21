#include "client.h"
#include "Funcs.h"

QString client_login = "";

Client::Client(QObject *parent) : QObject(parent)
{
    client_sock = new QTcpSocket(this);
    client_sock->connectToHost(ipAddress, 12345);
    connect(client_sock,SIGNAL(connected()),SLOT(slot_connected()));
    connect(client_sock,SIGNAL(readyRead()),SLOT(slot_readyRead()));
}

Client::~Client()
{
    client_sock->disconnectFromHost();
}

void Client::slot_connected()
{
    qDebug() << "Connected!!!";
}

void Client::slot_disconnected()
{
    client_sock->close();
}

void Client::parsing(QString msg)
{
    if (msg == "successful login")
        emit serverSucAuth();
    if (msg == "invalid login or password")
        emit serverFailAuth();
    if (msg == "successful registration")
        emit serverSucReg();
    if (msg == "choose antoher login")
        emit serverFailReg();
}

void Client::slot_readyRead()
{
    QByteArray array;
    std::string message = "";

    while(client_sock->bytesAvailable()>0)
    {
        array = client_sock->readAll();
        message += array.toStdString();
    }
    parsing(QString::fromStdString(message));

    qDebug() << "server: " << QString::fromStdString(message); //del
}

void Client::receiveLogData(QString l_username, QString l_password)
{
    client_login = l_username;
    client_sock->write(server_query( "auth", l_username, l_password));
}

void Client::receiveRegData(QString l_username, QString l_password, QString l_verpassword)
{
   if (correctLogPass(l_username, l_password, l_verpassword))
       client_sock->write(server_query("reg", l_username, l_password));
   else
       emit clientFailVerifpass();
}

void Client::reconnect()
{
    client_sock->connectToHost(ipAddress, 12345);
}

void Client::receiveMessage(QString msg)
{
    if (!msg.isEmpty())
        client_sock->write(server_query("msg", client_login, "pudge_pidzhak", msg));
}

void Client::receiveChatCreation(QString chatname, QString contact)
{
    contact += "&" + client_login;
    client_sock->write(server_query("chatcrt", chatname, contact));
}


void Client::receiveAddUserToChat(QString chatname, QString newuser)
{
    client_sock->write(server_query("chatUserAdd", chatname, newuser));
    qDebug() << chatname << newuser;
}

