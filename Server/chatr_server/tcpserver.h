/**
*  \file
*  \brief Заголовочный файл с описанием класса TcpServer, а также его полей и слотов
*
*  Данный файл содержит в себе описание класса, используемого для реализации сервера проекта.
*/

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
#include <QSslSocket>

/**
 * @brief The tcpServer class: наследник QObject
 *
 * Данный класс отвечает за реализацию сервера в проекте SSSchat.
 *
 * Он содержит в себе несколько публичных слотов, отвечающих за установление соединения,
 * приемку сообщений от клиента, отправку сообщений клиенту,
 * а также за разрыв соединения.
 *
 * Кроме того данный класс содержит в себе все необходимые поля, участвующие в реализации
 * "общения" между сервером и клиентами.
 */
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
    //void slotServerLoadMessage();
    void slotServerWriteMessage(string message);
    void slotServerSendChatlist(string login);
    void slotLoadChatRoom(string servmsg);

private:
    QTcpServer * serv;
    QTcpSocket * sock;
    QSslSocket *socket = new QSslSocket(this);
    bool server_status;
    int user_counts;
    std::string msg;
    QMap<int, QTcpSocket*> mp;
    const QString ipAddress = "127.0.0.1";
};

#endif // TCPSERVER_H
