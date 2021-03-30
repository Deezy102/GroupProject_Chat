#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <string>
#include <map>
#include <QDebug>
#include <fstream>
#include <QTcpSocket>

#include "database.h"
//bd-connect
#include <QtSql/QtSql>
//#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

using std::map;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;

bool check(string logpass);
map<string, string> read_from_file();
bool write_to_file(map<string, string> &mp);
bool registration(string logpass);



#endif // FUNCTIONS_H
