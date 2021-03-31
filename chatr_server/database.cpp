#include "database.h"

database::database()
{



}
bool reg_check(string login, string password){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "db_connect");
    db.setHostName("localhost");
    db.setDatabaseName("chat");
    db.setUserName("postgres");
    db.setPassword("1234");
    if (db.open()){
        qDebug() << "db open";
    }
    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name");
    qr.bindValue(":name", QString::fromStdString(login));
    qr.exec();
    if (qr.size()==0){
        qr.prepare("insert into users (login, password) values (?, ?)");
        qr.addBindValue(QString::fromStdString(login));
        qr.addBindValue(QString::fromStdString(password));
        qr.exec();
        db.close();
        return true;
    }
    else {
        db.close();
        return false;
    }
    qr.exec();
}

bool auth_check(string login, string password){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "db_connect");
    db.setHostName("localhost");
    db.setDatabaseName("chat");
    db.setUserName("postgres");
    db.setPassword("1234");
    if (db.open()){
        qDebug() << "db open";
    }

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name and password like :password");
    qr.bindValue(":name", QString::fromStdString(login));
    qr.bindValue(":password", QString::fromStdString(password));
    qr.exec();

    if (qr.size() == 1){
        db.close();
        return true;
    }
    else {
        qDebug() << "<3";
        db.close();
        return false;
    }

}
