#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

using std::string;


class database
{

public:


    database();
    QSqlDatabase db;

private:

};

bool auth_check(string login, string pass);
bool reg_check(string login, string pass);

#endif // DATABASE_H
