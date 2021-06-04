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
void Client::parsing(QString msg)
{
    qDebug() << "input parsing: " + msg;

    if (msg == "successful login"){
        QByteArray answer = "list&" + client_login.toUtf8();
        client_sock->write(answer);
        emit serverSucAuth();
    }
    if (msg == "invalid login or password")
        emit serverFailAuth();
    if (msg == "successful registration")
        emit serverSucReg();
    if (msg == "choose antoher login")
        emit serverFailReg();
    if (msg.contains("list&")){
        msg.remove(0, 5);
        msg.replace("&", "\n" );
        this->setChats(msg);
    }
    if (msg.contains("somethinmg")){
        //some
        m_messages = "";
    }

}
/**
 * @brief Client::slot_readyRead считывает сообщение от сервера и вызывает функцию парсинга
 */
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
/**
 * @brief Client::receiveLogData отправка данных авторизации
 * @param l_username - логин пользователя
 * @param l_password - пароль пользователя
 */
void Client::receiveLogData(QString l_username, QString l_password)
{
    client_login = l_username;
    client_sock->write(server_query( "auth", l_username, l_password));
}
/**
 * @brief Client::receiveRegData отправка данных регистрации
 * @param l_username - логин пользователя
 * @param l_password - пароль пользователя
 * @param l_verpassword - подтверждение пароля
 */
void Client::receiveRegData(QString l_username, QString l_password, QString l_verpassword)
{

   if (correctLogPass(l_username, l_password, l_verpassword)){
       qDebug() << "reg";
       client_sock->write(server_query("reg", l_username, l_password));}
   else
       emit clientFailVerifpass();
}
/**
 * @brief Client::reconnect настраивает новое подключение
 */
void Client::reconnect()
{
    client_sock->connectToHost(ipAddress, 12345);
}
/**
 * @brief Client::receiveMessage отправка данных для сообщений чатов
 * @param msg - текст сообщения
 */
void Client::receiveMessage(QString msg)
{
    if (!msg.isEmpty())
        client_sock->write(server_query("msg", client_login, "pudge_pidzhak", msg));
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
        qDebug() << "XYI";
        contact = client_login + "&" + contact;
        client_sock->write(server_query("chatcrt", chatname, contact));
    }
}

/**
 * @brief Client::receiveAddUserToChat отправка данных для добавления пользователя в чат
 * @param chatname - название чата
 * @param newuser - имя добавляемого пользователя
 */
void Client::receiveAddUserToChat(QString chatname, QString newuser)
{
    client_sock->write(server_query("chatUserAdd", chatname, newuser));
    //qDebug() << chatname << newuser;
}

void Client::receiveCurrenChat(QString chatname)
{
    if (m_chats.contains(chatname)){
        emit correctChat();
        cur_chat = chatname;
        client_sock->write("chatld&"+client_login.toUtf8()+"&"+cur_chat.toUtf8());
        qDebug() << m_chats;
        //this->setMessages("sjgoiSJoisej");
    }
    else {
        emit incorrectChat();
    }
}
