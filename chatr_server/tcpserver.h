#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "database.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>



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

private:
    QTcpServer * serv;
    QTcpSocket * sock;
    bool server_status;
    int user_counts;
    std::string msg;
    QMap<int, QTcpSocket*> mp;
signals:
    bool check(string logpass);
};

QByteArray parsing(string msg);

#endif // TCPSERVER_H
