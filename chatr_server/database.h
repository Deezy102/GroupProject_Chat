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
#include <iostream>
#include <QDateTime>
#include <cstdio>

using std::map;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::pair;
using std::string;

string read_from_file(string chatName);
bool write_to_file(string login, string chatName, string msg);


QSqlDatabase init_db();
//void close_db(QSqlDatabase db, QString db_name);

QByteArray parsing(string msg);
QByteArray authorization(string logpass);
QByteArray registration(string logpass);
QByteArray message(string msgData);

void discon(int socket_id);

#endif // DATABASE_H
