#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <string>
#include <fstream>
#include <iostream>
#include <QDateTime>
#include <cstdio>
#include <vector>

using std::map;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::pair;
using std::string;
using std::vector;

QByteArray read_from_file(string chatName, int counterNum);
bool write_to_file(string login, string chatName, string msg);


QSqlDatabase init_db();
//void close_db(QSqlDatabase db, QString db_name);

QByteArray parsing(string msg);
QByteArray authorization(string logpass);
QByteArray registration(string logpass);
QByteArray message(string msgData);
QByteArray chatCreation(string chatData);
QByteArray chatUserAdd(string msgData);
QByteArray chatUserDel(string msgData);

void BDSocketClear(int socket_id);
void oldSocketsClear();
int loginToSocket(string login);


#endif // DATABASE_H
