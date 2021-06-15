/**
* \file
* \brief Данный файл отвечает за реализацию класса Client
*
* В данном классе представлена реализация конструктора и деструктора класса Client,
* а также реализация слотов, отвечающих за клиент-серверное "общение"
*
*/
#include "client.h"
#include "Funcs.h"

QString client_login = "";
/**
 * @brief Client::Client конструктор класса.
 * @param parent указатель на родительский класс.
 */
Client::Client(QObject *parent) : QObject(parent)
{
    client_sock = new QTcpSocket(this);
    client_sock->connectToHost(ipAddress, 12345);

    if (client_sock->isValid())
        encryp.generatePairKey(pubcl, privcl, QRSAEncryption::Rsa::RSA_128);

    connect(client_sock,SIGNAL(connected()),SLOT(slot_connected()));
    connect(client_sock,SIGNAL(readyRead()),SLOT(slot_readyRead()));
}

void Client::setChats(const QString &a)
{
    if (a != m_chats) {
        m_chats = a;
        emit chatsChanged();
    }
}

void Client::setMessages(const QString &a)
{
    if (a != m_messages) {
        m_messages = a;
        emit messagesChanged();
    }
}

/**
 * @brief Client::~Client деструктор класса.
 */
Client::~Client()
{
    client_sock->disconnectFromHost();
}
/**
 * @brief Client::slot_connected вызывается при подключении к серверу
 */
void Client::slot_connected()
{
    qDebug() << "Connected!!!";
}
/**
 * @brief Client::slot_disconnected вызывается при отключении от сервера
 */
void Client::slot_disconnected()
{
    client_sock->close();
}
/**
 * @brief Client::parsing занимается парсингом сообщений от сервера
 * @param msg - сообщение от сервера
 */
void Client::parsing(QByteArray msg)
{
    if (msg == "successful login"){
        QByteArray answer = server_query("list", client_login);
        QByteArray encodeData = encryption(answer, privcl, pubcl, servkey);
        client_sock->write(encodeData);
        emit serverSucAuth();
    }
    if (msg == "successful chat creation")
    {
        QByteArray answer = server_query("list", client_login);
        QByteArray encodeData = encryption(answer, privcl, pubcl, servkey);
        client_sock->write(encodeData);
    }

    if (msg == "invalid login or password")
        emit serverFailAuth();
    if (msg == "successful registration")
        emit serverSucReg();
    if (msg == "choose antoher login")
        emit serverFailReg();

    if (msg.contains("list&"))
    {
        msg.remove(0, 5);
        msg.replace("&", "\n" );

        this->setChats(msg);
    }
    if (msg.contains("chatld&"))
    {
        msg.remove(0, 7);
        msg.replace("&", "\n");

        this->setMessages(msg);
    }
}
/**
 * @brief Client::slot_readyRead считывает сообщение от сервера и вызывает функцию парсинга
 */
void Client::slot_readyRead()
{
    QByteArray array;

    while(client_sock->bytesAvailable()>0)
        array = client_sock->readAll();

    if (servkey.length() == 0)
        servkey = array;
    else {
        QByteArray parsData = encryp.decode(array, privcl, QRSAEncryption::RSA_128);
        parsing(parsData);
    }

}
/**
 * @brief Client::receiveLogData отправка данных авторизации
 * @param l_username - логин пользователя
 * @param l_password - пароль пользователя
 */
void Client::receiveLogData(QString l_username, QString l_password)
{
    client_login = l_username;

    QByteArray msg = server_query( "auth", l_username, l_password);
    QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
    client_sock->write(encodeData1);
}
/**
 * @brief Client::receiveRegData отправка данных регистрации
 * @param l_username - логин пользователя
 * @param l_password - пароль пользователя
 * @param l_verpassword - подтверждение пароля
 */
void Client::receiveRegData(QString l_username, QString l_password, QString l_verpassword)
{
    if (correctLogPass(l_username, l_password, l_verpassword))
    {
        QByteArray msg = server_query("reg", l_username, l_password);
        QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
        client_sock->write(encodeData1);
    }
    else
        emit clientFailVerifpass();
}
/**
 * @brief Client::reconnect настраивает новое подключение
 */
void Client::reconnect()
{
    if (client_sock->state() == 3)
    {
        qDebug() << "is valid";
    }
    else
    {
        servkey.clear();
        encryp.generatePairKey(pubcl, privcl, QRSAEncryption::RSA_128);

        QByteArray garbage = client_sock->readAll();
        client_sock->connectToHost(ipAddress, 12345);
    }
}
/**
 * @brief Client::receiveMessage отправка данных для сообщений чатов
 * @param msg - текст сообщения
 */
void Client::receiveMessage(QString message)
{
    if (!message.isEmpty())
    {
        QByteArray msg = server_query("msg", client_login, cur_chat, message);
        QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
        client_sock->write(encodeData1);
    }
}
/**
 * @brief Client::receiveChatCreation отправка данных для создания чата
 * @param chatname - название чата
 * @param contact - имя второго пользователя
 */
void Client::receiveChatCreation(QString chatname, QString contact)
{
    if (checkText(chatname, "") && checkText(contact, ""))
    {
        contact = client_login + "&" + contact;
        QByteArray msg = server_query("chatcrt", chatname, contact);
        QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
        client_sock->write(encodeData1);
    }
}

/**
 * @brief Client::receiveAddUserToChat отправка данных для добавления пользователя в чат
 * @param chatname - название чата
 * @param newuser - имя добавляемого пользователя
 */
void Client::receiveAddUserToChat(QString chatname, QString newuser)
{
    QByteArray msg = server_query("chatUserAdd", chatname, newuser);
    QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
    client_sock->write(encodeData1);
}

void Client::receiveCurrenChat(QString chatname)
{
    if (m_chats.contains(chatname)){
        emit correctChat();
        cur_chat = chatname;
        QByteArray msg = server_query("chatld", client_login, cur_chat);
        QByteArray encodeData1 = encryption(msg, privcl, pubcl, servkey);
        client_sock->write(encodeData1);
    }
    else {
        emit incorrectChat();
    }
}
