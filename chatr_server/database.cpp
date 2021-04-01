#include "database.h"

bool flag = true;

map<string, string> read_from_file() {

    std::map<string, string> mp;
    ifstream file("D:\\chat\\db_test\\db.txt", std::ios::in);
    if (!file.is_open()) {
        qDebug() << "try again";
    }
    else {
        while (!file.eof()) {
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

bool write_to_file(map<string, string> &mp)
{
    map<string, string>::iterator iter;
    ofstream file;
    file.open("D:\\chat\\db_test\\db.txt", ofstream::out | ofstream::trunc);
    if (file.is_open() == true) {
        for (iter = mp.begin(); iter != mp.end(); iter++) {
            file << (*iter).first << " " << iter->second << std::endl;
        }
        file.close();
        return true;
    }
    else {

        return false;
    }

}

QByteArray parsing(string msg)
{
    string buf = msg.substr(0,msg.find("&"));
    msg.erase(0,buf.size() + 1);

    if (buf == "auth")
        return authorization(msg);
    if (buf == "reg")
        return registration(msg);

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
    QString password = QString::fromStdString(logpass.substr(logpass.rfind("&"), logpass.length()));

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
    QString password = QString::fromStdString(logpass.substr(logpass.rfind("&"), logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name and password like :password");
    qr.bindValue(":name", login);
    qr.bindValue(":password", password);
    qr.exec();

    bool flag_qr = qr.size();

    db.close();

    if (flag_qr)
        return "successful login";

    return "invalid login or password";
}
