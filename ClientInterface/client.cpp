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

void Client::slot_connected()
{
    qDebug() << "Connected!!!";
}

void Client::slot_disconnected()
{
    client_sock->close();
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
    qDebug() << QString::fromStdString(message);
    qDebug() << client_login;
}

void Client::receiveLogData(QString l_username, QString l_password)
{
    client_login = l_username;
    client_sock->write(server_query(l_username, l_password, "auth"));
}

void Client::receiveRegData(QString l_username, QString l_password, QString l_verpassword)
{
   if (correctLogPass(l_username, l_password, l_verpassword))
   {
       client_sock->write(server_query(l_username, l_password, "reg"));
   }
   else
   qDebug() << "invalid verifpass";

}

void Client::reconnect()
{
    client_sock->connectToHost(ipAddress, 12345);
}
