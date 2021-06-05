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
#include <qrsaencryption.h>
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
    Q_PROPERTY(QString chats READ chats WRITE setChats NOTIFY chatsChanged)
    Q_PROPERTY(QString messages READ messages WRITE setMessages NOTIFY messagesChanged)
public:
    explicit Client(QObject *parent = nullptr);
    void setChats(const QString &a);
    QString chats() const {
           return m_chats;
    }

    void setMessages(const QString &a);

    QString messages() const {
        return m_messages;
 }
    ~Client();
signals:
    void serverSucReg(); // сигнал удачной регистарции
    void serverFailReg(); // сигнал провальной регистрации
    void serverSucAuth();
    void serverFailAuth();
    void clientFailVerifpass();
    void chatsChanged();
    void messagesChanged();
    void correctChat();
    void incorrectChat();
public slots:
    void receiveLogData(QString l_username, QString l_password);
    void receiveRegData(QString l_username, QString l_password, QString l_verpassword);
    void parsing(QByteArray msg);
    void reconnect();
    void receiveMessage(QString msg);
    void receiveChatCreation(QString chatname, QString contact);
    void receiveAddUserToChat(QString chatname, QString newuser);
    void receiveCurrenChat(QString chatname);

private slots:
    void slot_connected();
    void slot_readyRead();
    void slot_disconnected();


private:
    QTcpSocket *client_sock;
    const QString ipAddress = "localhost";

    QString m_chats = "jopa\nhui\npizda\nanal\nmanal";
    QString cur_chat;
    QString m_messages;

    QRSAEncryption encryp;
    QByteArray pubcl, privcl;
    QByteArray servkey;


};


#endif // CLIENT_H
