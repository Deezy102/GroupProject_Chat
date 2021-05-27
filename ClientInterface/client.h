/**
*  \file
*  \brief Заголовочный файл с описанием класса Client, а также его полей, сигналов и слотов.
*
*  Данный файл содержит в себе описание класса, используемого для реализации клиента проекта.
*/
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <string>
#include <QTcpSocket>

/**
 * @brief class Client наследник QObject
 * Данный класс отвечает за реализацию клиента в проекте SSSchat.
 *
 * Он содержит в себе несколько публичных и приватных слотов, отвечающих за установление соединения,
 * приемку различных сообщений от сервера, отправку сообщений серверу,
 * а также за разрыв соединения.
 *
 * Кроме того данный класс содержит в себе все необходимые поля, участвующие в реализации
 * "общения" между сервером и клиентами.
 */
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    ~Client();
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
    void receiveChatCreation(QString chatname, QString contact);
    void receiveAddUserToChat(QString chatname, QString newuser);

private slots:
    void slot_connected();
    void slot_readyRead();
    void slot_disconnected();


private:
    QTcpSocket *client_sock;
    const QString ipAddress = "127.0.0.1";
};


#endif // CLIENT_H
