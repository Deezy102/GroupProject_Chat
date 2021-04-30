#include "database.h"

bool flag = true;
const string path = "D:\\chat\\chat_git\\GroupProject_Chat\\chatStorage\\";

map<string, string> read_from_file()
{

    std::map<string, string> mp;
    ifstream file("D:\\chat\\db_test\\db.txt", std::ios::in);
    if (!file.is_open())
    {
        qDebug() << "try again";
    }
    else
    {
        while (!file.eof())
        {
            string name;
            string pass;
            file >> name;
            file >> pass;
            mp.insert(make_pair(name, pass));
        }
    }
    file.close();
    return mp;
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

QByteArray parsing(string msg)
{
    string buf = msg.substr(0,msg.find("&"));
    msg.erase(0,buf.size() + 1);

    if (buf == "auth")
        return authorization(msg);
    if (buf == "reg")
        return registration(msg);
    if (buf == "msg")
        return message(msg);
    return "error";
}

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
        qr.prepare("insert into users (login, password) values (?, ?)");
        qr.addBindValue(login);
        qr.addBindValue(password);
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
    QString password = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name and password like :password");
    qr.bindValue(":name", login);
    qr.bindValue(":password", password);
    qr.exec();

    int flag_qr = qr.size();

    db.close();

    if (flag_qr == 1)
        return "successful login";

    return "invalid login or password";
}

QByteArray message(string msgData)
{
    qDebug() << QString::fromStdString(msgData);
    string login = msgData.substr(0,msgData.find("&"));
    msgData.erase(0,login.size() + 1);
    string chatName = msgData.substr(0, msgData.find("&"));
    msgData.erase(0,chatName.size() + 1);
    string msg = msgData;
    qDebug() << QString::fromStdString(login) << QString::fromStdString(chatName) << QString::fromStdString(msg);
    write_to_file(login, chatName, msg);
    return "null";
}














