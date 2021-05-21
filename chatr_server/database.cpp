#include "database.h"

bool flag = true;
const string path = "D:\\Chat_project\\GroupProject_Chat\\chatStorage\\";

string read_from_file(string chatName, int serialNum)
{
    //сериалНум - порядковый номер сообщения которое необходимо вывести
    //для слотСерверВрайтМесседж значение вшито в код и равно 0(новейшее сообщение переписки)
    //для слотЛодЧатРум задается итератором из заданного множителем диапазона(первая подгрузка переписки и просмотр старых сообщений)
    string str;
    ifstream file(path + chatName + ".txt", std::ios::in);
    if (!file.is_open())
    {
        qDebug() << "try again";
    }
    else
    {

        string buf;
        int counter = 0;
        //цикл переводит курсор на нужную строку
        while (!file.eof() && counter < serialNum)
        {
            std::getline(file, buf);
            counter++;
            buf = "";
        }
        //считываем нужное сообщение
        std::getline(file, buf);
        str = "mChat&" + buf;//подумал, что надо добавить какой-то флаг для вычленения сообщения на клиенте
    }

    file.close();
    //добавить проверку на пустоту строки, чтобы не забивать модели пустыми сообщениями
    return str;
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
        db.setPassword("1234");
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
    //qDebug() << QString::fromStdString(logpass);

    QString login = QString::fromStdString(logpass.substr(0,logpass.find("&")));
    QString password = QString::fromStdString(logpass.substr(logpass.find("&") + 1, logpass.rfind("&") - logpass.find("&") - 1));
    QString socket = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    //qDebug() << "logpass" << login << " " << password << " " << socket;

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name and password like :password");
    qr.bindValue(":name", login);
    qr.bindValue(":password", password);
    qr.exec();

    int flag_qr = qr.size();

    if (flag_qr == 1)
    {
        qr.prepare("update users set current_socket = :socket where login like :name;");
        qr.bindValue(":socket", socket);
        qr.bindValue(":name", login);
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
    //qDebug() << QString::fromStdString(login) << QString::fromStdString(chatName) << QString::fromStdString(msg);
    write_to_file(login, chatName, msg);
    string buf = "msg&" +chatName;
    return QByteArray::fromStdString(buf);
            //QByteArray::fromStdString(read_from_file(chatName));
}

void BDSocketClear(int socket_id)
{
    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);

    qr.prepare("update users set current_socket = null where current_socket = :socket_id;");
    qr.bindValue(":socket_id", QString::number(socket_id));
    qr.exec();

    db.close();
}

int loginToSocket(std::string login)
{
    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);

    qr.prepare("select current_socket from users where login like :login");
    qr.bindValue(":login", QString::fromStdString(login));

    int rtrn = -1;

    qr.exec();

    qr.next();

    rtrn = qr.value(0).toInt();

    //qDebug() << rtrn;
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

    qDebug() << "chatcreation" << chatName << contact1 << contact2;

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from chatlist where chatname like :chatName");
    qr.bindValue(":chatName", chatName);
    qr.exec();

    if (qr.size()==0)
    {
        qr.prepare(QString("insert into chatlist (chatname, userlist) values ('%1', '{%2, %3}')").arg(chatName).arg(contact1).arg(contact2));
        qr.exec();
        //qDebug() << "error: " << qr.lastError().text(); //ВЫВОД ОШИБКИ ЗАПРОСА БД
        db.close();

        return "successful chat creation";
    }

    db.close();

    return "bad name of chat";


    qDebug() << "chatcrt: " << QString::fromStdString(chatData);
    return "chat created";
}

vector<string> getChatlist(string login){

    vector<string> list;

    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);
    //запос к бд на вывод всех чатов по логину
    qr.prepare("select chatname from chatlist where array_length(array_positions(userlist, :logname), 1) > 0;");
    qr.bindValue(":logname", QString::fromStdString(login));
    qr.exec();
    //добавляем названия чата в вектор стрингов
    while(qr.next())
        list.push_back(qr.value(0).toString().toStdString() + ";");

    db.close();

    return list;
}
