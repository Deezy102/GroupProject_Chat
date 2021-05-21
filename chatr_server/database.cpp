#include "database.h"

bool flag = true;
const string path = "D:\\chat\\chat_git\\GroupProject_Chat\\chatStorage\\";

QByteArray read_from_file(string chatName, int counterNum)
{
    string str;
    ifstream file(path + chatName + ".txt", std::ios::in);
    if (!file.is_open())
    {
        qDebug() << "try again";
    }
    else
    {
        int counter = 0;
        while (!file.eof() && counter < counterNum)
        {
            string buf;
            std::getline(file, buf);
            str += buf + " &";
            counter++;
        }
    }
    file.close();
    return QByteArray::fromStdString(str);
}

bool write_to_file(string login, string chatName, string msg)
{
    ifstream oldFile;
    oldFile.open(path + chatName + ".txt", ifstream::in);

    if (oldFile.is_open() == true)
    {
        ofstream newFile;
        newFile.open(path + chatName + "_temp.txt", ofstream::out | ofstream::app | ofstream::ate);

        if (newFile.is_open())
        {
            QString time_format = "dd-MM-yy  HH:mm";
            QDateTime qdate = QDateTime::currentDateTime();
            QString sdate = qdate.toString(time_format);

            newFile << "(" << sdate.QString::toStdString() << ")" << login << ": " << msg << std::endl;

            string buf;
            while (getline(oldFile, buf))
                newFile << buf << std::endl;
        }

        oldFile.close();
        newFile.close();

        string oldPath = path + chatName + ".txt";
        string newPath = path + chatName + "_temp.txt";
        const char *oldChar = oldPath.c_str();
        const char *newChar = newPath.c_str();

        remove(oldChar);
        rename(newChar, oldChar);

        return true;
    }
    else
    {
        ofstream createFile;
        createFile.open(path + chatName + ".txt", ofstream::out);
        createFile.close();
        write_to_file(login, chatName, msg);
    }
    return true;
}

//QByteArray parsing(string msg)
//{
//    string buf = msg.substr(0,msg.find("&"));
//    msg.erase(0,buf.size() + 1);

//    if (buf == "auth")
//        return authorization(msg);
//    if (buf == "reg")
//        return registration(msg);
//    if (buf == "msg")
//        return message(msg);
//    return "error";
//}

QSqlDatabase init_db()
{
    QSqlDatabase db;
    if (flag)
    {
        db = QSqlDatabase::addDatabase("QPSQL", "db_connect");
        db.setHostName("localhost");
        db.setDatabaseName("chat");
        db.setUserName("postgres");
        db.setPassword("    ");
        flag = false;
    }
    else
        db = QSqlDatabase::database("db_connect");
    if (db.open())
        qDebug() << "db has opened";
    else
        qDebug() << "db has not opened";
    return db;
}

QByteArray registration(string logpass)
{
    QString login = QString::fromStdString(logpass.substr(0,logpass.find("&")));
    QString password = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name");
    qr.bindValue(":name", login);
    qr.exec();

    if (qr.size()==0)
    {
        qr.prepare(QString("insert into users (login, password) values ('%1', '%2')").arg(login,password));
        qr.exec();

        db.close();

        return "successful registration";
    }

    db.close();

    return "choose antoher login";
}

QByteArray authorization(string logpass)
{
    QString login = QString::fromStdString(logpass.substr(0,logpass.find("&")));
    QString password = QString::fromStdString(logpass.substr(logpass.find("&") + 1, logpass.rfind("&") - logpass.find("&") - 1));
    QString socket = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare(QString("select count(*) from users where login like '%1' and password like '%2'").arg(login,password));
    qr.exec();
    qr.next();

    if (qr.value(0).toInt() == 1)
    {
        qr.prepare(QString("update users set current_socket = '%1' where login like '%2';").arg(socket,login));
        qr.exec();
        db.close();
        return "successful login";
    }

    db.close();
    return "invalid login or password";
}

QByteArray message(string msgData)
{
    string login = msgData.substr(0,msgData.find("&"));
    msgData.erase(0,login.size() + 1);
    string chatName = msgData.substr(0, msgData.find("&"));
    msgData.erase(0,chatName.size() + 1);
    string msg = msgData;

    write_to_file(login, chatName, msg);

    return QByteArray::fromStdString("msg&" +chatName);
}

void BDSocketClear(int socket_id)
{
    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);

    qr.prepare(QString("update users set current_socket = null where current_socket = %1;").arg(socket_id));
    qr.exec();

    db.close();
}

int loginToSocket(std::string login)
{
    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);

    qr.prepare(QString("select current_socket from users where login like '%1'").arg(QString::fromStdString(login)));
    qr.exec();
    qr.next();

    int rtrn = -1;
    rtrn = qr.value(0).toInt();

    db.close();
    return rtrn;
}

void oldSocketsClear()
{
    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);

    qr.prepare("update users set current_socket = null where current_socket > -1;");
    qr.exec();

    db.close();
}

QByteArray chatCreation(std::string chatData)
{
    QString chatName = QString::fromStdString(chatData.substr(0, chatData.find("&")));
    chatData.erase(0,chatName.size() + 1);
    QString contact1 = QString::fromStdString(chatData.substr(0, chatData.find("&")));
    chatData.erase(0, chatData.find("&") + 1);
    QString contact2 = QString::fromStdString(chatData);


    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare(QString("select * from chatlist where chatname like '%1'").arg(chatName));
    qr.exec();

    if (qr.size()==0)
    {
        qr.prepare(QString("insert into chatlist (chatname, userlist) values ('%1', '{%2, %3}')").arg(chatName, contact1, contact2));
        qr.exec();
        //qDebug() << "error: " << qr.lastError().text(); //ВЫВОД ОШИБКИ ЗАПРОСА БД
        db.close();

        return "successful chat creation";
    }

    db.close();

    return "bad name of chat";
}

QByteArray chatUserAdd(std::string msgData)
{
    QString chatName = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    msgData.erase(0,chatName.size() + 1);
    QString userLogin = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    //msgData.erase(0,chatName.size() + 1);

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    QString buf = "select count(*) from chatlist where chatname = '%1' and not('%2' = ANY(userlist)) and (select count(*) from users where login like '%2') = 1;";
    qr.prepare(buf.arg(chatName, userLogin));
    qr.exec();
    qr.next();

    if (qr.value(0).toInt() == 1)
    {
        qr.prepare(QString("update chatlist set userlist = userlist || '{%1}' where chatname like '%2'").arg(userLogin, chatName));
        qr.exec();

        db.close();

        return "successful user addition";
    }

    db.close();

    return "fail user addition";
}


QByteArray chatUserDel(std::string msgData)
{
    QString chatName = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    msgData.erase(0,chatName.size() + 1);
    QString userLogin = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    //msgData.erase(0,chatName.size() + 1);

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    QString buf = "update chatlist set userlist = array_remove_item((select userlist from chatlist where chatname like '%1'), '%2')where chatname like '%1';";
    qr.prepare(buf.arg(chatName, userLogin));
    qr.exec();

    return "user deleted";
}
