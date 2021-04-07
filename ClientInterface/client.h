#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <string>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

signals:
    void serverSucReg(); // сигнал удачной регистарции
    void serverFailReg(); // сигнал провальной регистрации
    void serverSucAuth();
    void serverFailAuth();
    void clientFailVerifpass();

public slots:
    void receiveLogData(QString l_username, QString l_password);
    void receiveRegData(QString l_username, QString l_password, QString l_verpassword);
    void parsing(QString msg);
    void reconnect();
    void receiveMessage(QString msg);

private slots:
    void slot_connected();
    void slot_readyRead();
    //void slot_send_to_server(QString message);
    void slot_disconnected();


private:
    QTcpSocket *client_sock;
    const QString ipAddress = "127.0.0.1";
};


#endif // CLIENT_H
