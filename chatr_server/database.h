#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <string>
#include <fstream>

using std::map;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;

map<string, string> read_from_file();
bool write_to_file(map<string, string> &mp);


QSqlDatabase init_db();
void close_db(QSqlDatabase db, QString db_name);

QByteArray parsing(string msg);
QByteArray authorization(string logpass);
QByteArray registration(string logpass);

#endif // DATABASE_H
